/*
 * Copyright (C) 2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/**
 * @file  patch.c
 * @brief Patching some of the .so internal functions or bridging them to native
 *        for better compatibility.
 */

#include <kubridge.h>
#include <so_util/so_util.h>
#include "utils/logger.h"

extern so_module so_mod;

void so_patch(void) {
    // Fix screen resolution mapping in Game::GetObfuscateFilename
    // On Vita, screen width is 960 and height is 544.
    // At 0x144784, the game checks if height == 540 (qHD). If so, it branches to 0x144a40
    // to map 960x540 to 854x480 (854P480_*.FAK assets in OBB).
    // On Vita, height is 544, so the check fails, leaving 960x544, for which no assets exist in the OBB.
    // We patch the branch at 0x144788 (beq 0x144a40 -> b 0x144a40, opcode 0xea0000ac)
    // so that any 960-width screen unconditionally maps to 854x480.
    uint32_t b_144a40 = 0xea0000ac; // b 0x144a40
    kuKernelCpuUnrestrictedMemcpy((void *)(so_mod.text_base + 0x144788), &b_144a40, sizeof(b_144a40));
    l_info("Patched Game::GetObfuscateFilename resolution check (960x544 -> 854x480).");

    // STLport std::_Filebuf_base::_M_page_size (0x669744) defaults to 0 and is set via sysconf(_SC_PAGESIZE).
    // If it is 0, _Underflow::_M_doit divides by it when reading XML files, causing SIGFPE.
    uint32_t *m_page_size = (uint32_t *)(so_mod.text_base + 0x669744);
    *m_page_size = 4096;
    l_info("Initialized std::_Filebuf_base::_M_page_size to 4096.");

    // ControlsMenu::IsComboValid(bool&) en 0x0020e600 -> siempre retornar 1 (valido)
    // Permite guardar y usar cualquier esquema de control sin que el juego lo rechace
    // ARM: mov r0, #1 (0xe3a00001); bx lr (0xe12fff1e)
    uint32_t patch_combo_valid[] = { 0xe3a00001, 0xe12fff1e };
    kuKernelCpuUnrestrictedMemcpy((void *)(so_mod.text_base + 0x20e600), patch_combo_valid, sizeof(patch_combo_valid));
    l_info("Patched ControlsMenu::IsComboValid to always return 1.");

    // Control por defecto en CGameSettings::ResetControls() (0x2c2d50):
    // Cambiar mov ip, #2 (0xe3a0c002, acelerometro) a mov ip, #0 (0xe3a0c000, botones/triggers)
    uint32_t default_steering_buttons = 0xe3a0c000;
    kuKernelCpuUnrestrictedMemcpy((void *)(so_mod.text_base + 0x2c2d50), &default_steering_buttons, sizeof(default_steering_buttons));
    l_info("Patched CGameSettings::ResetControls default steering to SideButtons.");

    // Pantalla blanca/cuelgue al iniciar carrera (010.log): el hilo principal gira a
    // ~1M fread+fwrite/s sobre saves/tracking_data1.dat + tracking_data2.dat sin avanzar,
    // colgado dentro de onDraw en la pantalla de info de licencia (barra de progreso vacía).
    // glot::TrackingManager::LoadEvents() en 0x0047a0b4 (ARM, verificado por objdump) relee
    // y migra esos ficheros en pushEventToMessageQueue/callbackFinishSendEvents; con los
    // servidores caídos el contenido nunca converge y el bucle no termina. Los servidores
    // están muertos así que la telemetría es inútil: devolver 0 ("sin eventos guardados",
    // igual que un primer arranque sin saves, caso que el juego ya maneja) y no entrar.
    // ARM: mov r0, #0 (0xe3a00000); bx lr (0xe12fff1e)
    uint32_t patch_tracking_loadevents[] = { 0xe3a00000, 0xe12fff1e };
    kuKernelCpuUnrestrictedMemcpy((void *)(so_mod.text_base + 0x47a0b4), patch_tracking_loadevents, sizeof(patch_tracking_loadevents));
    l_info("Patched glot::TrackingManager::LoadEvents to no-op (return 0).");
}

