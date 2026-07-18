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



void setup_scr_alarm_set_screen(lv_ui *ui)
{
    //Write codes alarm_set_screen
    ui->alarm_set_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->alarm_set_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->alarm_set_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for alarm_set_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_set_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_set_screen_cont_1
    ui->alarm_set_screen_cont_1 = lv_obj_create(ui->alarm_set_screen);
    lv_obj_set_pos(ui->alarm_set_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->alarm_set_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->alarm_set_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for alarm_set_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_set_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->alarm_set_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->alarm_set_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->alarm_set_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_set_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_set_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_set_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_set_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_set_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_set_screen_alarm_set_back_btn
    ui->alarm_set_screen_alarm_set_back_btn = lv_btn_create(ui->alarm_set_screen_cont_1);
    ui->alarm_set_screen_alarm_set_back_btn_label = lv_label_create(ui->alarm_set_screen_alarm_set_back_btn);
    lv_label_set_text(ui->alarm_set_screen_alarm_set_back_btn_label, "");
    lv_label_set_long_mode(ui->alarm_set_screen_alarm_set_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->alarm_set_screen_alarm_set_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->alarm_set_screen_alarm_set_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->alarm_set_screen_alarm_set_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->alarm_set_screen_alarm_set_back_btn, 5, 215);
    lv_obj_set_size(ui->alarm_set_screen_alarm_set_back_btn, 30, 20);

    //Write style for alarm_set_screen_alarm_set_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_alarm_set_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_alarm_set_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_alarm_set_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_set_screen_alarm_set_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_set_screen_alarm_set_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_alarm_set_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->alarm_set_screen_alarm_set_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->alarm_set_screen_alarm_set_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->alarm_set_screen_alarm_set_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_alarm_set_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_alarm_set_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_alarm_set_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_alarm_set_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_set_screen_hour_roller
    ui->alarm_set_screen_hour_roller = lv_roller_create(ui->alarm_set_screen_cont_1);
    lv_roller_set_options(ui->alarm_set_screen_hour_roller, "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n00", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_pos(ui->alarm_set_screen_hour_roller, 30, 50);
    lv_obj_set_width(ui->alarm_set_screen_hour_roller, 60);

    //Write style for alarm_set_screen_hour_roller, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->alarm_set_screen_hour_roller, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_hour_roller, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_hour_roller, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_hour_roller, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_hour_roller, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_hour_roller, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_hour_roller, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_hour_roller, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_set_screen_hour_roller, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->alarm_set_screen_hour_roller, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->alarm_set_screen_hour_roller, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->alarm_set_screen_hour_roller, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_set_screen_hour_roller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_set_screen_hour_roller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_hour_roller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for alarm_set_screen_hour_roller, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_hour_roller, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_hour_roller, lv_color_hex(0xffbf00), LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_hour_roller, LV_GRAD_DIR_NONE, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_hour_roller, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_hour_roller, &lv_Font_8, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_hour_roller, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);

    lv_roller_set_visible_row_count(ui->alarm_set_screen_hour_roller, 5);
    //Write codes alarm_set_screen_minute_roller_1
    ui->alarm_set_screen_minute_roller_1 = lv_roller_create(ui->alarm_set_screen_cont_1);
    lv_roller_set_options(ui->alarm_set_screen_minute_roller_1, "0\n1\n2\n3\n4\n5", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_pos(ui->alarm_set_screen_minute_roller_1, 130, 50);
    lv_obj_set_width(ui->alarm_set_screen_minute_roller_1, 60);

    //Write style for alarm_set_screen_minute_roller_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->alarm_set_screen_minute_roller_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_minute_roller_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_minute_roller_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_minute_roller_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_minute_roller_1, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_minute_roller_1, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_minute_roller_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_minute_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_set_screen_minute_roller_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->alarm_set_screen_minute_roller_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->alarm_set_screen_minute_roller_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->alarm_set_screen_minute_roller_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_set_screen_minute_roller_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_set_screen_minute_roller_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_minute_roller_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for alarm_set_screen_minute_roller_1, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_minute_roller_1, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_minute_roller_1, lv_color_hex(0xffbf00), LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_minute_roller_1, LV_GRAD_DIR_NONE, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_minute_roller_1, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_minute_roller_1, &lv_Font_8, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_minute_roller_1, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);

    lv_roller_set_visible_row_count(ui->alarm_set_screen_minute_roller_1, 5);
    //Write codes alarm_set_screen_alarm_set_label
    ui->alarm_set_screen_alarm_set_label = lv_label_create(ui->alarm_set_screen_cont_1);
    lv_label_set_text(ui->alarm_set_screen_alarm_set_label, "闹钟设置");
    lv_label_set_long_mode(ui->alarm_set_screen_alarm_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->alarm_set_screen_alarm_set_label, 5, 5);
    lv_obj_set_size(ui->alarm_set_screen_alarm_set_label, 75, 15);

    //Write style for alarm_set_screen_alarm_set_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_alarm_set_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_alarm_set_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_alarm_set_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_alarm_set_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_alarm_set_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_set_screen_separation_label
    ui->alarm_set_screen_separation_label = lv_label_create(ui->alarm_set_screen_cont_1);
    lv_label_set_text(ui->alarm_set_screen_separation_label, ":");
    lv_label_set_long_mode(ui->alarm_set_screen_separation_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->alarm_set_screen_separation_label, 100, 110);
    lv_obj_set_size(ui->alarm_set_screen_separation_label, 20, 20);

    //Write style for alarm_set_screen_separation_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_separation_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_separation_label, &lv_Font_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_separation_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_separation_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_separation_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_set_screen_confirm_btn
    ui->alarm_set_screen_confirm_btn = lv_btn_create(ui->alarm_set_screen_cont_1);
    ui->alarm_set_screen_confirm_btn_label = lv_label_create(ui->alarm_set_screen_confirm_btn);
    lv_label_set_text(ui->alarm_set_screen_confirm_btn_label, "确定");
    lv_label_set_long_mode(ui->alarm_set_screen_confirm_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->alarm_set_screen_confirm_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->alarm_set_screen_confirm_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->alarm_set_screen_confirm_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->alarm_set_screen_confirm_btn, 270, 110);
    lv_obj_set_size(ui->alarm_set_screen_confirm_btn, 40, 20);

    //Write style for alarm_set_screen_confirm_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_confirm_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_confirm_btn, lv_color_hex(0xffb765), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_confirm_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_set_screen_confirm_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_set_screen_confirm_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_confirm_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_confirm_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_confirm_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_confirm_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_confirm_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_set_screen_minute_roller_2
    ui->alarm_set_screen_minute_roller_2 = lv_roller_create(ui->alarm_set_screen_cont_1);
    lv_roller_set_options(ui->alarm_set_screen_minute_roller_2, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_pos(ui->alarm_set_screen_minute_roller_2, 195, 50);
    lv_obj_set_width(ui->alarm_set_screen_minute_roller_2, 60);

    //Write style for alarm_set_screen_minute_roller_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->alarm_set_screen_minute_roller_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_minute_roller_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_minute_roller_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_minute_roller_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_minute_roller_2, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_minute_roller_2, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_minute_roller_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_set_screen_minute_roller_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_set_screen_minute_roller_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->alarm_set_screen_minute_roller_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->alarm_set_screen_minute_roller_2, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->alarm_set_screen_minute_roller_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_set_screen_minute_roller_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_set_screen_minute_roller_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_set_screen_minute_roller_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for alarm_set_screen_minute_roller_2, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_set_screen_minute_roller_2, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_set_screen_minute_roller_2, lv_color_hex(0xffbf00), LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_set_screen_minute_roller_2, LV_GRAD_DIR_NONE, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_set_screen_minute_roller_2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_set_screen_minute_roller_2, &lv_Font_8, LV_PART_SELECTED|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_set_screen_minute_roller_2, 255, LV_PART_SELECTED|LV_STATE_DEFAULT);

    lv_roller_set_visible_row_count(ui->alarm_set_screen_minute_roller_2, 5);
    //The custom code of alarm_set_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->alarm_set_screen);

    //Init events for screen.
    events_init_alarm_set_screen(ui);
}
