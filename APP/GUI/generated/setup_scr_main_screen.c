/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_main_screen(lv_ui *ui)
{
    //Write codes main_screen
    ui->main_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->main_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_cont_1
    ui->main_screen_cont_1 = lv_obj_create(ui->main_screen);
    lv_obj_set_pos(ui->main_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->main_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_cont_1, lv_color_hex(0xfafafa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_time_label
    ui->main_screen_time_label = lv_label_create(ui->main_screen_cont_1);
    lv_label_set_text(ui->main_screen_time_label, "14:13:30");
    lv_label_set_long_mode(ui->main_screen_time_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_time_label, 135, 35);
    lv_obj_set_size(ui->main_screen_time_label, 170, 35);

    //Write style for main_screen_time_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_time_label, lv_color_hex(0x02edf7), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_time_label, &lv_font_montserrat_40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_time_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_time_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_week_label
    ui->main_screen_week_label = lv_label_create(ui->main_screen_cont_1);
    lv_label_set_text(ui->main_screen_week_label, "星期二");
    lv_label_set_long_mode(ui->main_screen_week_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_week_label, 69, 60);
    lv_obj_set_size(ui->main_screen_week_label, 60, 20);

    //Write style for main_screen_week_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_week_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_week_label, &lv_Font_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_week_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_week_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_week_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_indoor_cont
    ui->main_screen_indoor_cont = lv_obj_create(ui->main_screen_cont_1);
    lv_obj_set_pos(ui->main_screen_indoor_cont, 5, 95);
    lv_obj_set_size(ui->main_screen_indoor_cont, 150, 140);
    lv_obj_set_scrollbar_mode(ui->main_screen_indoor_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen_indoor_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_indoor_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_screen_indoor_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_screen_indoor_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_screen_indoor_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_indoor_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_indoor_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_indoor_cont, lv_color_hex(0x83abed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_indoor_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_indoor_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_indoor_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_indoor_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_indoor_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_indoor_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_indoor_label
    ui->main_screen_indoor_label = lv_label_create(ui->main_screen_indoor_cont);
    lv_label_set_text(ui->main_screen_indoor_label, "室内环境");
    lv_label_set_long_mode(ui->main_screen_indoor_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_indoor_label, 35, 4);
    lv_obj_set_size(ui->main_screen_indoor_label, 70, 20);

    //Write style for main_screen_indoor_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_indoor_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_indoor_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_indoor_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_indoor_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_indoor_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_temperature_label
    ui->main_screen_temperature_label = lv_label_create(ui->main_screen_indoor_cont);
    lv_label_set_text(ui->main_screen_temperature_label, "温度:18℃");
    lv_label_set_long_mode(ui->main_screen_temperature_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_temperature_label, 30, 25);
    lv_obj_set_size(ui->main_screen_temperature_label, 90, 18);

    //Write style for main_screen_temperature_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_temperature_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_temperature_label, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_temperature_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_temperature_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_temperature_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_air_pressure_label
    ui->main_screen_air_pressure_label = lv_label_create(ui->main_screen_indoor_cont);
    lv_label_set_text(ui->main_screen_air_pressure_label, "气压:988hpa");
    lv_label_set_long_mode(ui->main_screen_air_pressure_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_air_pressure_label, 5, 75);
    lv_obj_set_size(ui->main_screen_air_pressure_label, 130, 20);

    //Write style for main_screen_air_pressure_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_air_pressure_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_air_pressure_label, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT); 
    lv_obj_set_style_text_opa(ui->main_screen_air_pressure_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_air_pressure_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_air_pressure_label, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_air_pressure_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_humidity_label
    ui->main_screen_humidity_label = lv_label_create(ui->main_screen_indoor_cont);
    lv_label_set_text(ui->main_screen_humidity_label, "湿度:100%RH");
    lv_label_set_long_mode(ui->main_screen_humidity_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_humidity_label, 20, 50);
    lv_obj_set_size(ui->main_screen_humidity_label, 110, 18);

    //Write style for main_screen_humidity_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_humidity_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_humidity_label, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT); 
    lv_obj_set_style_text_opa(ui->main_screen_humidity_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_humidity_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_air_q_label
    ui->main_screen_air_q_label = lv_label_create(ui->main_screen_indoor_cont);
    lv_label_set_text(ui->main_screen_air_q_label, "空气质量：优");
    lv_label_set_long_mode(ui->main_screen_air_q_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_air_q_label, 5, 110);
    lv_obj_set_size(ui->main_screen_air_q_label, 130, 20);

    //Write style for main_screen_air_q_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_air_q_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_air_q_label, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT); 
    lv_obj_set_style_text_opa(ui->main_screen_air_q_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_air_q_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_air_q_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_extern_cont
    ui->main_screen_extern_cont = lv_obj_create(ui->main_screen_cont_1);
    lv_obj_set_pos(ui->main_screen_extern_cont, 175, 95);
    lv_obj_set_size(ui->main_screen_extern_cont, 130, 140);
    lv_obj_set_scrollbar_mode(ui->main_screen_extern_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen_extern_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_extern_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_screen_extern_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_screen_extern_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_screen_extern_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_extern_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_extern_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_extern_cont, lv_color_hex(0xffa300), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_extern_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_extern_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_extern_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_extern_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_extern_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_extern_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_address_img
    ui->main_screen_address_img = lv_img_create(ui->main_screen_extern_cont);
    lv_obj_add_flag(ui->main_screen_address_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_screen_address_img, "0:/PICTURE/software_icon/address_icon.bin");
    lv_img_set_pivot(ui->main_screen_address_img, 48,48);
    lv_img_set_angle(ui->main_screen_address_img, 0);
    lv_obj_set_pos(ui->main_screen_address_img, 20, 1);
    lv_obj_set_size(ui->main_screen_address_img, 32, 32);

    //Write style for main_screen_address_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->main_screen_address_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_screen_address_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->main_screen_address_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_screen_address_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_address_label
    ui->main_screen_address_label = lv_label_create(ui->main_screen_extern_cont);
    lv_label_set_text(ui->main_screen_address_label, "贵港");
    lv_label_set_long_mode(ui->main_screen_address_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_address_label, 60, 10);
    lv_obj_set_size(ui->main_screen_address_label, 50, 20);

    //Write style for main_screen_address_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_address_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_address_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_address_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_address_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_address_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_extern_temp_label
    ui->main_screen_extern_temp_label = lv_label_create(ui->main_screen_extern_cont);
    lv_label_set_text(ui->main_screen_extern_temp_label, "28℃");
    lv_label_set_long_mode(ui->main_screen_extern_temp_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_extern_temp_label, 13, 95);
    lv_obj_set_size(ui->main_screen_extern_temp_label, 100, 20);

    //Write style for main_screen_extern_temp_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_extern_temp_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_extern_temp_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_extern_temp_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_extern_temp_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_extern_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_wea_status_label
    ui->main_screen_wea_status_label = lv_label_create(ui->main_screen_extern_cont);
    lv_label_set_text(ui->main_screen_wea_status_label, "多云");
    lv_label_set_long_mode(ui->main_screen_wea_status_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_wea_status_label, 20, 60);
    lv_obj_set_size(ui->main_screen_wea_status_label, 80, 20);

    //Write style for main_screen_wea_status_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_wea_status_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_wea_status_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_wea_status_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_wea_status_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_wea_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_date_label
    ui->main_screen_date_label = lv_label_create(ui->main_screen_cont_1);
    lv_label_set_text(ui->main_screen_date_label, "2026/7/7");
    lv_label_set_long_mode(ui->main_screen_date_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_date_label, 0, 30);
    lv_obj_set_size(ui->main_screen_date_label, 110, 20);

    //Write style for main_screen_date_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_date_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_date_label, &lv_Font_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_date_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_date_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_wifi_img
    ui->main_screen_wifi_img = lv_img_create(ui->main_screen_cont_1);
    lv_obj_add_flag(ui->main_screen_wifi_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_screen_wifi_img, "0:/PICTURE/software_icon/wifi_icon.bin");
    lv_img_set_pivot(ui->main_screen_wifi_img, 50,50);
    lv_img_set_angle(ui->main_screen_wifi_img, 0);
    lv_obj_set_pos(ui->main_screen_wifi_img, 275, 0);
    lv_obj_set_size(ui->main_screen_wifi_img, 32, 32);

    //Write style for main_screen_wifi_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_wifi_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_screen_wifi_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_wifi_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_screen_wifi_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_light_btn
    ui->main_screen_light_btn = lv_btn_create(ui->main_screen_cont_1);
    ui->main_screen_light_btn_label = lv_label_create(ui->main_screen_light_btn);
    lv_label_set_text(ui->main_screen_light_btn_label, "亮度设置");
    lv_label_set_long_mode(ui->main_screen_light_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_light_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_light_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->main_screen_light_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->main_screen_light_btn, 5, 5);
    lv_obj_set_size(ui->main_screen_light_btn, 55, 15);

    //Write style for main_screen_light_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_light_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_light_btn, lv_color_hex(0xfafafa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_light_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_light_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_light_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_light_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_light_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_light_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_light_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_light_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_light_set_cont
    ui->main_screen_light_set_cont = lv_obj_create(ui->main_screen_cont_1);
    lv_obj_set_pos(ui->main_screen_light_set_cont, 10, 30);
    lv_obj_set_size(ui->main_screen_light_set_cont, 300, 50);
    lv_obj_set_scrollbar_mode(ui->main_screen_light_set_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_screen_light_set_cont, LV_OBJ_FLAG_HIDDEN);

    //Write style for main_screen_light_set_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_light_set_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_screen_light_set_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_screen_light_set_cont, lv_color_hex(0xd4d5d5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_screen_light_set_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_light_set_cont, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_light_set_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_light_set_cont, lv_color_hex(0xfafafa), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_light_set_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_light_set_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_light_set_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_light_set_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_light_set_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_light_set_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_light_slider
    ui->main_screen_light_slider = lv_slider_create(ui->main_screen_light_set_cont);
    lv_slider_set_range(ui->main_screen_light_slider, 0, 100);
    lv_slider_set_mode(ui->main_screen_light_slider, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->main_screen_light_slider, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->main_screen_light_slider, 21, 20);
    lv_obj_set_size(ui->main_screen_light_slider, 198, 6);

    //Write style for main_screen_light_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_light_slider, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_light_slider, lv_color_hex(0xa5acb3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_light_slider, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_light_slider, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->main_screen_light_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_light_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_light_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_light_slider, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_light_slider, lv_color_hex(0xaec5d6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_light_slider, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_light_slider, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for main_screen_light_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_light_slider, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_light_slider, lv_color_hex(0x6c8294), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_light_slider, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_light_slider, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes main_screen_light_value_label
    ui->main_screen_light_value_label = lv_label_create(ui->main_screen_light_set_cont);
    lv_label_set_text(ui->main_screen_light_value_label, "50%");
    lv_label_set_long_mode(ui->main_screen_light_value_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_light_value_label, 230, 15);
    lv_obj_set_size(ui->main_screen_light_value_label, 45, 15);

    //Write style for main_screen_light_value_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_light_value_label, lv_color_hex(0xbd8686), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_light_value_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_light_value_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_light_value_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_light_value_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_cancel_imgbtn
    ui->main_screen_cancel_imgbtn = lv_imgbtn_create(ui->main_screen_light_set_cont);
    lv_imgbtn_set_src(ui->main_screen_cancel_imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, "0:/PICTURE/software_icon/cancel_icon.bin", NULL);
    ui->main_screen_cancel_imgbtn_label = lv_label_create(ui->main_screen_cancel_imgbtn);
    lv_label_set_text(ui->main_screen_cancel_imgbtn_label, "");
    lv_label_set_long_mode(ui->main_screen_cancel_imgbtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_cancel_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_cancel_imgbtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->main_screen_cancel_imgbtn, 278, 2);
    lv_obj_set_size(ui->main_screen_cancel_imgbtn, 16, 16);

    //Write style for main_screen_cancel_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->main_screen_cancel_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_cancel_imgbtn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_cancel_imgbtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_cancel_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_screen_cancel_imgbtn, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_cancel_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->main_screen_cancel_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->main_screen_cancel_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->main_screen_cancel_imgbtn, &lv_Font_7, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->main_screen_cancel_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for main_screen_cancel_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->main_screen_cancel_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->main_screen_cancel_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->main_screen_cancel_imgbtn, &lv_Font_7, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->main_screen_cancel_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for main_screen_cancel_imgbtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_cancel_imgbtn, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->main_screen_cancel_imgbtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes main_screen_auto_light_sw
    ui->main_screen_auto_light_sw = lv_switch_create(ui->main_screen_cont_1);
    lv_obj_set_pos(ui->main_screen_auto_light_sw, 65, 3);
    lv_obj_set_size(ui->main_screen_auto_light_sw, 40, 20);

    //Write style for main_screen_auto_light_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_auto_light_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_auto_light_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_auto_light_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_auto_light_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_auto_light_sw, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_auto_light_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_screen_auto_light_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->main_screen_auto_light_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->main_screen_auto_light_sw, lv_color_hex(0x929aa0), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_auto_light_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->main_screen_auto_light_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for main_screen_auto_light_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_auto_light_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_auto_light_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_auto_light_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_auto_light_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_auto_light_sw, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes main_screen_battery_img
    ui->main_screen_battery_img = lv_img_create(ui->main_screen_cont_1);
    lv_obj_add_flag(ui->main_screen_battery_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_screen_battery_img, "0:/PICTURE/software_icon/battery_icon.bin");
    lv_img_set_pivot(ui->main_screen_battery_img, 50,50);
    lv_img_set_angle(ui->main_screen_battery_img, 0);
    lv_obj_set_pos(ui->main_screen_battery_img, 210, 2);
    lv_obj_set_size(ui->main_screen_battery_img, 32, 24);

    //Write style for main_screen_battery_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_battery_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_screen_battery_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_battery_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_screen_battery_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_battery_label
    ui->main_screen_battery_label = lv_label_create(ui->main_screen_cont_1);
    lv_label_set_text(ui->main_screen_battery_label, "100%");
    lv_label_set_long_mode(ui->main_screen_battery_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_battery_label, 240, 10);
    lv_obj_set_size(ui->main_screen_battery_label, 40, 10);

    //Write style for main_screen_battery_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_battery_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_battery_label, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_battery_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_battery_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_battery_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->main_screen);

    //Init events for screen.
    events_init_main_screen(ui);
}
