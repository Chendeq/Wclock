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



void setup_scr_software_screen(lv_ui *ui)
{
    //Write codes software_screen
    ui->software_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->software_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->software_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for software_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_cont_1
    ui->software_screen_cont_1 = lv_obj_create(ui->software_screen);
    lv_obj_set_pos(ui->software_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->software_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->software_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for software_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->software_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->software_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->software_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->software_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->software_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_cont_1, lv_color_hex(0xf9f7f7), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->software_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->software_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->software_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->software_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_setting_btn
    ui->software_screen_setting_btn = lv_btn_create(ui->software_screen_cont_1);
    ui->software_screen_setting_btn_label = lv_label_create(ui->software_screen_setting_btn);
    lv_label_set_text(ui->software_screen_setting_btn_label, "设置");
    lv_label_set_long_mode(ui->software_screen_setting_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->software_screen_setting_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->software_screen_setting_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->software_screen_setting_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->software_screen_setting_btn, 40, 65);
    lv_obj_set_size(ui->software_screen_setting_btn, 40, 20);

    //Write style for software_screen_setting_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen_setting_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_setting_btn, lv_color_hex(0x5882a6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_setting_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->software_screen_setting_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_setting_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_setting_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->software_screen_setting_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->software_screen_setting_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->software_screen_setting_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->software_screen_setting_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_setting_img
    ui->software_screen_setting_img = lv_img_create(ui->software_screen_cont_1);
    lv_obj_add_flag(ui->software_screen_setting_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->software_screen_setting_img, "0:/PICTURE/software_icon/setting_icon.bin");
    lv_img_set_pivot(ui->software_screen_setting_img, 50,50);
    lv_img_set_angle(ui->software_screen_setting_img, 0);
    lv_obj_set_pos(ui->software_screen_setting_img, 35, 10);
    lv_obj_set_size(ui->software_screen_setting_img, 48, 48);

    //Write style for software_screen_setting_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->software_screen_setting_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->software_screen_setting_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_setting_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->software_screen_setting_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_weather_img
    ui->software_screen_weather_img = lv_img_create(ui->software_screen_cont_1);
    lv_obj_add_flag(ui->software_screen_weather_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->software_screen_weather_img, "0:/PICTURE/software_icon/weather_icon.bin");
    lv_img_set_pivot(ui->software_screen_weather_img, 50,50);
    lv_img_set_angle(ui->software_screen_weather_img, 0);
    lv_obj_set_pos(ui->software_screen_weather_img, 140, 10);
    lv_obj_set_size(ui->software_screen_weather_img, 48, 48);

    //Write style for software_screen_weather_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->software_screen_weather_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->software_screen_weather_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_weather_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->software_screen_weather_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_weather_btn
    ui->software_screen_weather_btn = lv_btn_create(ui->software_screen_cont_1);
    ui->software_screen_weather_btn_label = lv_label_create(ui->software_screen_weather_btn);
    lv_label_set_text(ui->software_screen_weather_btn_label, "天气");
    lv_label_set_long_mode(ui->software_screen_weather_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->software_screen_weather_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->software_screen_weather_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->software_screen_weather_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->software_screen_weather_btn, 145, 65);
    lv_obj_set_size(ui->software_screen_weather_btn, 40, 20);

    //Write style for software_screen_weather_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen_weather_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_weather_btn, lv_color_hex(0x5882a6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_weather_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->software_screen_weather_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_weather_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_weather_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->software_screen_weather_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->software_screen_weather_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->software_screen_weather_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->software_screen_weather_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_calendar_img
    ui->software_screen_calendar_img = lv_img_create(ui->software_screen_cont_1);
    lv_obj_add_flag(ui->software_screen_calendar_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->software_screen_calendar_img, "0:/PICTURE/software_icon/calendar_icon.bin");
    lv_img_set_pivot(ui->software_screen_calendar_img, 50,50);
    lv_img_set_angle(ui->software_screen_calendar_img, 0);
    lv_obj_set_pos(ui->software_screen_calendar_img, 240, 10);
    lv_obj_set_size(ui->software_screen_calendar_img, 48, 48);

    //Write style for software_screen_calendar_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->software_screen_calendar_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->software_screen_calendar_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_calendar_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->software_screen_calendar_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_calendar_btn
    ui->software_screen_calendar_btn = lv_btn_create(ui->software_screen_cont_1);
    ui->software_screen_calendar_btn_label = lv_label_create(ui->software_screen_calendar_btn);
    lv_label_set_text(ui->software_screen_calendar_btn_label, "日历");
    lv_label_set_long_mode(ui->software_screen_calendar_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->software_screen_calendar_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->software_screen_calendar_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->software_screen_calendar_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->software_screen_calendar_btn, 245, 65);
    lv_obj_set_size(ui->software_screen_calendar_btn, 40, 20);

    //Write style for software_screen_calendar_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen_calendar_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_calendar_btn, lv_color_hex(0x5882a6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_calendar_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->software_screen_calendar_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_calendar_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_calendar_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->software_screen_calendar_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->software_screen_calendar_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->software_screen_calendar_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->software_screen_calendar_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_calculate_img
    ui->software_screen_calculate_img = lv_img_create(ui->software_screen_cont_1);
    lv_obj_add_flag(ui->software_screen_calculate_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->software_screen_calculate_img, "0:/PICTURE/software_icon/calculator_icon.bin");
    lv_img_set_pivot(ui->software_screen_calculate_img, 50,50);
    lv_img_set_angle(ui->software_screen_calculate_img, 0);
    lv_obj_set_pos(ui->software_screen_calculate_img, 35, 100);
    lv_obj_set_size(ui->software_screen_calculate_img, 48, 48);

    //Write style for software_screen_calculate_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->software_screen_calculate_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->software_screen_calculate_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_calculate_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->software_screen_calculate_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_calculate_btn
    ui->software_screen_calculate_btn = lv_btn_create(ui->software_screen_cont_1);
    ui->software_screen_calculate_btn_label = lv_label_create(ui->software_screen_calculate_btn);
    lv_label_set_text(ui->software_screen_calculate_btn_label, "计算器");
    lv_label_set_long_mode(ui->software_screen_calculate_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->software_screen_calculate_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->software_screen_calculate_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->software_screen_calculate_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->software_screen_calculate_btn, 30, 155);
    lv_obj_set_size(ui->software_screen_calculate_btn, 60, 20);

    //Write style for software_screen_calculate_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen_calculate_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_calculate_btn, lv_color_hex(0x5882a6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_calculate_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->software_screen_calculate_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_calculate_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_calculate_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->software_screen_calculate_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->software_screen_calculate_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->software_screen_calculate_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->software_screen_calculate_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_peripheral_btn
    ui->software_screen_peripheral_btn = lv_btn_create(ui->software_screen_cont_1);
    ui->software_screen_peripheral_btn_label = lv_label_create(ui->software_screen_peripheral_btn);
    lv_label_set_text(ui->software_screen_peripheral_btn_label, "外设");
    lv_label_set_long_mode(ui->software_screen_peripheral_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->software_screen_peripheral_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->software_screen_peripheral_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->software_screen_peripheral_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->software_screen_peripheral_btn, 245, 155);
    lv_obj_set_size(ui->software_screen_peripheral_btn, 40, 20);

    //Write style for software_screen_peripheral_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen_peripheral_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_peripheral_btn, lv_color_hex(0x5882a6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_peripheral_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->software_screen_peripheral_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_peripheral_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_peripheral_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->software_screen_peripheral_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->software_screen_peripheral_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->software_screen_peripheral_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->software_screen_peripheral_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_peripheral_img
    ui->software_screen_peripheral_img = lv_img_create(ui->software_screen_cont_1);
    lv_obj_add_flag(ui->software_screen_peripheral_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->software_screen_peripheral_img, "0:/PICTURE/software_icon/peripheral_icon.bin");
    lv_img_set_pivot(ui->software_screen_peripheral_img, 50,50);
    lv_img_set_angle(ui->software_screen_peripheral_img, 0);
    lv_obj_set_pos(ui->software_screen_peripheral_img, 240, 100);
    lv_obj_set_size(ui->software_screen_peripheral_img, 48, 48);

    //Write style for software_screen_peripheral_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->software_screen_peripheral_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->software_screen_peripheral_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_peripheral_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->software_screen_peripheral_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_file_img
    ui->software_screen_file_img = lv_img_create(ui->software_screen_cont_1);
    lv_obj_add_flag(ui->software_screen_file_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->software_screen_file_img, "0:/PICTURE/software_icon/file_icon.bin");
    lv_img_set_pivot(ui->software_screen_file_img, 50,50);
    lv_img_set_angle(ui->software_screen_file_img, 0);
    lv_obj_set_pos(ui->software_screen_file_img, 140, 100);
    lv_obj_set_size(ui->software_screen_file_img, 48, 48);

    //Write style for software_screen_file_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->software_screen_file_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->software_screen_file_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_file_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->software_screen_file_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes software_screen_file_btn
    ui->software_screen_file_btn = lv_btn_create(ui->software_screen_cont_1);
    ui->software_screen_file_btn_label = lv_label_create(ui->software_screen_file_btn);
    lv_label_set_text(ui->software_screen_file_btn_label, "文件");
    lv_label_set_long_mode(ui->software_screen_file_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->software_screen_file_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->software_screen_file_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->software_screen_file_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->software_screen_file_btn, 143, 155);
    lv_obj_set_size(ui->software_screen_file_btn, 40, 20);

    //Write style for software_screen_file_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->software_screen_file_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->software_screen_file_btn, lv_color_hex(0x5882a6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->software_screen_file_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->software_screen_file_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->software_screen_file_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->software_screen_file_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->software_screen_file_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->software_screen_file_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->software_screen_file_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->software_screen_file_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of software_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->software_screen);

    //Init events for screen.
    events_init_software_screen(ui);
}
