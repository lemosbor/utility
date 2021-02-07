/* Copyright 2017 Benjamin Kesselring
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#define LOCKING_SUPPORT_ENABLE // блокировка клавиш для капс локов
#define LOCKING_RESYNC_ENABLE // синхронизация светодиода с каспами
#define TAPPING_TERM 200 // задержка для клавиш двойного назначения
// #define IGNORE_MOD_TAP_INTERRUPT
// #define PERMISSIVE_HOLD
#define COMBO_TERM 20 // задержка для комбо
#define COMBO_COUNT 47 // количество спец. комбинаций с клавишами
#define COMBO_ALLOW_ACTION_KEY

#define ONESHOT_TAP_TOGGLE 2 // ожидающие кнопки. Количество нажатий для залипания.
#define ONESHOT_TIMEOUT 2000  // ожидающие кнопки. время ожидания (мс)

// place overrides here
