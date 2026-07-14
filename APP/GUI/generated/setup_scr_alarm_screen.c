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



void setup_scr_alarm_screen(lv_ui *ui)
{
    //Write codes alarm_screen
    ui->alarm_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->alarm_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->alarm_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for alarm_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_cont_1
    ui->alarm_screen_cont_1 = lv_obj_create(ui->alarm_screen);
    lv_obj_set_pos(ui->alarm_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->alarm_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->alarm_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for alarm_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->alarm_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->alarm_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->alarm_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_back_btn
    ui->alarm_screen_alarm_back_btn = lv_btn_create(ui->alarm_screen_cont_1);
    ui->alarm_screen_alarm_back_btn_label = lv_label_create(ui->alarm_screen_alarm_back_btn);
    lv_label_set_text(ui->alarm_screen_alarm_back_btn_label, "");
    lv_label_set_long_mode(ui->alarm_screen_alarm_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->alarm_screen_alarm_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->alarm_screen_alarm_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->alarm_screen_alarm_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->alarm_screen_alarm_back_btn, 5, 215);
    lv_obj_set_size(ui->alarm_screen_alarm_back_btn, 30, 20);

    //Write style for alarm_screen_alarm_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->alarm_screen_alarm_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->alarm_screen_alarm_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->alarm_screen_alarm_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_screen_alarm_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_screen_alarm_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_screen_alarm_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_screen_alarm_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_set_btn_1
    ui->alarm_screen_alarm_set_btn_1 = lv_btn_create(ui->alarm_screen_cont_1);
    ui->alarm_screen_alarm_set_btn_1_label = lv_label_create(ui->alarm_screen_alarm_set_btn_1);
    lv_label_set_text(ui->alarm_screen_alarm_set_btn_1_label, "");
    lv_label_set_long_mode(ui->alarm_screen_alarm_set_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->alarm_screen_alarm_set_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->alarm_screen_alarm_set_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->alarm_screen_alarm_set_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->alarm_screen_alarm_set_btn_1, 50, 40);
    lv_obj_set_size(ui->alarm_screen_alarm_set_btn_1, 100, 30);

    //Write style for alarm_screen_alarm_set_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_set_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_set_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_set_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_set_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_screen_alarm_set_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_screen_alarm_set_btn_1, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_screen_alarm_set_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_screen_alarm_set_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_set_btn_2
    ui->alarm_screen_alarm_set_btn_2 = lv_btn_create(ui->alarm_screen_cont_1);
    ui->alarm_screen_alarm_set_btn_2_label = lv_label_create(ui->alarm_screen_alarm_set_btn_2);
    lv_label_set_text(ui->alarm_screen_alarm_set_btn_2_label, "");
    lv_label_set_long_mode(ui->alarm_screen_alarm_set_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->alarm_screen_alarm_set_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->alarm_screen_alarm_set_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->alarm_screen_alarm_set_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->alarm_screen_alarm_set_btn_2, 50, 100);
    lv_obj_set_size(ui->alarm_screen_alarm_set_btn_2, 100, 30);

    //Write style for alarm_screen_alarm_set_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_set_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_set_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_set_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_set_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_screen_alarm_set_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_screen_alarm_set_btn_2, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_screen_alarm_set_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_screen_alarm_set_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_sw_1
    ui->alarm_screen_alarm_sw_1 = lv_switch_create(ui->alarm_screen_cont_1);
    lv_obj_set_pos(ui->alarm_screen_alarm_sw_1, 235, 45);
    lv_obj_set_size(ui->alarm_screen_alarm_sw_1, 40, 20);

    //Write style for alarm_screen_alarm_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for alarm_screen_alarm_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for alarm_screen_alarm_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_sw_2
    ui->alarm_screen_alarm_sw_2 = lv_switch_create(ui->alarm_screen_cont_1);
    lv_obj_set_pos(ui->alarm_screen_alarm_sw_2, 235, 105);
    lv_obj_set_size(ui->alarm_screen_alarm_sw_2, 40, 20);

    //Write style for alarm_screen_alarm_sw_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_sw_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_sw_2, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_sw_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_sw_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_sw_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_sw_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for alarm_screen_alarm_sw_2, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_sw_2, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_sw_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_sw_2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_sw_2, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for alarm_screen_alarm_sw_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_sw_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_sw_2, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_sw_2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_sw_2, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_sw_2, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_label_1
    ui->alarm_screen_alarm_label_1 = lv_label_create(ui->alarm_screen_cont_1);
    lv_label_set_text(ui->alarm_screen_alarm_label_1, "8:30");
    lv_label_set_long_mode(ui->alarm_screen_alarm_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->alarm_screen_alarm_label_1, 50, 40);
    lv_obj_set_size(ui->alarm_screen_alarm_label_1, 100, 30);

    //Write style for alarm_screen_alarm_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_screen_alarm_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_screen_alarm_label_1, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_screen_alarm_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_screen_alarm_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_label_1, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_label_1, lv_color_hex(0x4a4a4a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_screen_alarm_label_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_label_2
    ui->alarm_screen_alarm_label_2 = lv_label_create(ui->alarm_screen_cont_1);
    lv_label_set_text(ui->alarm_screen_alarm_label_2, "8:30");
    lv_label_set_long_mode(ui->alarm_screen_alarm_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->alarm_screen_alarm_label_2, 50, 100);
    lv_obj_set_size(ui->alarm_screen_alarm_label_2, 100, 30);

    //Write style for alarm_screen_alarm_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_screen_alarm_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_screen_alarm_label_2, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_screen_alarm_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_screen_alarm_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_label_2, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->alarm_screen_alarm_label_2, lv_color_hex(0x4a4a4a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->alarm_screen_alarm_label_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_screen_alarm_label_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes alarm_screen_alarm_title_label
    ui->alarm_screen_alarm_title_label = lv_label_create(ui->alarm_screen_cont_1);
    lv_label_set_text(ui->alarm_screen_alarm_title_label, "闹钟");
    lv_label_set_long_mode(ui->alarm_screen_alarm_title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->alarm_screen_alarm_title_label, 5, 5);
    lv_obj_set_size(ui->alarm_screen_alarm_title_label, 40, 15);

    //Write style for alarm_screen_alarm_title_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->alarm_screen_alarm_title_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->alarm_screen_alarm_title_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->alarm_screen_alarm_title_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->alarm_screen_alarm_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->alarm_screen_alarm_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of alarm_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->alarm_screen);

    //Init events for screen.
    events_init_alarm_screen(ui);
}
