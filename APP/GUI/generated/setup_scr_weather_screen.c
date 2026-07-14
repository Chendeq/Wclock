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



void setup_scr_weather_screen(lv_ui *ui)
{
    //Write codes weather_screen
    ui->weather_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->weather_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->weather_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weather_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_cont_1
    ui->weather_screen_cont_1 = lv_obj_create(ui->weather_screen);
    lv_obj_set_pos(ui->weather_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->weather_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->weather_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->weather_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->weather_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->weather_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->weather_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->weather_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_weather_back_btn
    ui->weather_screen_weather_back_btn = lv_btn_create(ui->weather_screen_cont_1);
    ui->weather_screen_weather_back_btn_label = lv_label_create(ui->weather_screen_weather_back_btn);
    lv_label_set_text(ui->weather_screen_weather_back_btn_label, "");
    lv_label_set_long_mode(ui->weather_screen_weather_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->weather_screen_weather_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->weather_screen_weather_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->weather_screen_weather_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->weather_screen_weather_back_btn, 5, 215);
    lv_obj_set_size(ui->weather_screen_weather_back_btn, 30, 20);

    //Write style for weather_screen_weather_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weather_screen_weather_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->weather_screen_weather_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->weather_screen_weather_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->weather_screen_weather_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_weather_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_weather_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->weather_screen_weather_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->weather_screen_weather_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->weather_screen_weather_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_weather_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_weather_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_weather_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_weather_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_day_label_1
    ui->weather_screen_day_label_1 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_day_label_1, "今天");
    lv_label_set_long_mode(ui->weather_screen_day_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_day_label_1, 40, 25);
    lv_obj_set_size(ui->weather_screen_day_label_1, 40, 15);

    //Write style for weather_screen_day_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_day_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_day_label_1, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_day_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_day_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_day_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_date_label_1
    ui->weather_screen_date_label_1 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_date_label_1, "11.18");
    lv_label_set_long_mode(ui->weather_screen_date_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_date_label_1, 35, 50);
    lv_obj_set_size(ui->weather_screen_date_label_1, 40, 12);

    //Write style for weather_screen_date_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_date_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_date_label_1, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_date_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_date_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_date_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_wea_label_1
    ui->weather_screen_wea_label_1 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_wea_label_1, "晴");
    lv_label_set_long_mode(ui->weather_screen_wea_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_wea_label_1, 35, 85);
    lv_obj_set_size(ui->weather_screen_wea_label_1, 40, 15);

    //Write style for weather_screen_wea_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_wea_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_wea_label_1, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_wea_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_wea_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_wea_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_day_img_1
    ui->weather_screen_day_img_1 = lv_img_create(ui->weather_screen_cont_1);
    lv_obj_add_flag(ui->weather_screen_day_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_screen_day_img_1, "0:/PICTURE/weather_icon/qing.bin");
    lv_img_set_pivot(ui->weather_screen_day_img_1, 50,50);
    lv_img_set_angle(ui->weather_screen_day_img_1, 0);
    lv_obj_set_pos(ui->weather_screen_day_img_1, 40, 118);
    lv_obj_set_size(ui->weather_screen_day_img_1, 32, 32);

    //Write style for weather_screen_day_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_screen_day_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_screen_day_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_day_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_screen_day_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_daytime_tem_label_1
    ui->weather_screen_daytime_tem_label_1 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_daytime_tem_label_1, "13℃~19℃");
    lv_label_set_long_mode(ui->weather_screen_daytime_tem_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_daytime_tem_label_1, 10, 175);
    lv_obj_set_size(ui->weather_screen_daytime_tem_label_1, 100, 15);

    //Write style for weather_screen_daytime_tem_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_daytime_tem_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_daytime_tem_label_1, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_daytime_tem_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_daytime_tem_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_daytime_tem_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_day_label_2
    ui->weather_screen_day_label_2 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_day_label_2, "明天");
    lv_label_set_long_mode(ui->weather_screen_day_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_day_label_2, 150, 25);
    lv_obj_set_size(ui->weather_screen_day_label_2, 40, 15);

    //Write style for weather_screen_day_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_day_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_day_label_2, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_day_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_day_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_day_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_date_label_2
    ui->weather_screen_date_label_2 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_date_label_2, "11.19");
    lv_label_set_long_mode(ui->weather_screen_date_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_date_label_2, 145, 50);
    lv_obj_set_size(ui->weather_screen_date_label_2, 40, 12);

    //Write style for weather_screen_date_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_date_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_date_label_2, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_date_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_date_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_date_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_wea_label_2
    ui->weather_screen_wea_label_2 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_wea_label_2, "多云");
    lv_label_set_long_mode(ui->weather_screen_wea_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_wea_label_2, 142, 85);
    lv_obj_set_size(ui->weather_screen_wea_label_2, 40, 15);

    //Write style for weather_screen_wea_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_wea_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_wea_label_2, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_wea_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_wea_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_wea_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_day_img_2
    ui->weather_screen_day_img_2 = lv_img_create(ui->weather_screen_cont_1);
    lv_obj_add_flag(ui->weather_screen_day_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_screen_day_img_2, "0:/PICTURE/weather_icon/yin.bin");
    lv_img_set_pivot(ui->weather_screen_day_img_2, 50,50);
    lv_img_set_angle(ui->weather_screen_day_img_2, 0);
    lv_obj_set_pos(ui->weather_screen_day_img_2, 148, 118);
    lv_obj_set_size(ui->weather_screen_day_img_2, 32, 32);

    //Write style for weather_screen_day_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_screen_day_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_screen_day_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_day_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_screen_day_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_daytime_tem_label_2
    ui->weather_screen_daytime_tem_label_2 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_daytime_tem_label_2, "15℃~26℃");
    lv_label_set_long_mode(ui->weather_screen_daytime_tem_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_daytime_tem_label_2, 115, 175);
    lv_obj_set_size(ui->weather_screen_daytime_tem_label_2, 100, 15);

    //Write style for weather_screen_daytime_tem_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_daytime_tem_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_daytime_tem_label_2, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_daytime_tem_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_daytime_tem_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_daytime_tem_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_daytime_tem_label_3
    ui->weather_screen_daytime_tem_label_3 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_daytime_tem_label_3, "14℃~20℃");
    lv_label_set_long_mode(ui->weather_screen_daytime_tem_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_daytime_tem_label_3, 220, 175);
    lv_obj_set_size(ui->weather_screen_daytime_tem_label_3, 100, 15);

    //Write style for weather_screen_daytime_tem_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_daytime_tem_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_daytime_tem_label_3, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_daytime_tem_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_daytime_tem_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_daytime_tem_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_day_img_3
    ui->weather_screen_day_img_3 = lv_img_create(ui->weather_screen_cont_1);
    lv_obj_add_flag(ui->weather_screen_day_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_screen_day_img_3, "0:/PICTURE/weather_icon/qing.bin");
    lv_img_set_pivot(ui->weather_screen_day_img_3, 50,50);
    lv_img_set_angle(ui->weather_screen_day_img_3, 0);
    lv_obj_set_pos(ui->weather_screen_day_img_3, 252, 118);
    lv_obj_set_size(ui->weather_screen_day_img_3, 32, 32);

    //Write style for weather_screen_day_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_screen_day_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_screen_day_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_day_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_screen_day_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_wea_label_3
    ui->weather_screen_wea_label_3 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_wea_label_3, "晴");
    lv_label_set_long_mode(ui->weather_screen_wea_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_wea_label_3, 245, 85);
    lv_obj_set_size(ui->weather_screen_wea_label_3, 40, 15);

    //Write style for weather_screen_wea_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_wea_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_wea_label_3, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_wea_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_wea_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_wea_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_date_label_3
    ui->weather_screen_date_label_3 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_date_label_3, "11.20");
    lv_label_set_long_mode(ui->weather_screen_date_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_date_label_3, 247, 50);
    lv_obj_set_size(ui->weather_screen_date_label_3, 40, 12);

    //Write style for weather_screen_date_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_date_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_date_label_3, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_date_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_date_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_date_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_day_label_3
    ui->weather_screen_day_label_3 = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_day_label_3, "后天");
    lv_label_set_long_mode(ui->weather_screen_day_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_day_label_3, 250, 25);
    lv_obj_set_size(ui->weather_screen_day_label_3, 40, 15);

    //Write style for weather_screen_day_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_day_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_day_label_3, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_day_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_day_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_day_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_screen_weather_title_label
    ui->weather_screen_weather_title_label = lv_label_create(ui->weather_screen_cont_1);
    lv_label_set_text(ui->weather_screen_weather_title_label, "天气预报");
    lv_label_set_long_mode(ui->weather_screen_weather_title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_screen_weather_title_label, 5, 3);
    lv_obj_set_size(ui->weather_screen_weather_title_label, 70, 20);

    //Write style for weather_screen_weather_title_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_screen_weather_title_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_screen_weather_title_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_screen_weather_title_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_screen_weather_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_screen_weather_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of weather_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->weather_screen);

    //Init events for screen.
    events_init_weather_screen(ui);
}
