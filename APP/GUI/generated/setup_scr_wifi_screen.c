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



void setup_scr_wifi_screen(lv_ui *ui)
{
    //Write codes wifi_screen
    ui->wifi_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->wifi_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->wifi_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for wifi_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->wifi_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes wifi_screen_cont_1
    ui->wifi_screen_cont_1 = lv_obj_create(ui->wifi_screen);
    lv_obj_set_pos(ui->wifi_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->wifi_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->wifi_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for wifi_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->wifi_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes wifi_screen_wifi_back_btn
    ui->wifi_screen_wifi_back_btn = lv_btn_create(ui->wifi_screen_cont_1);
    ui->wifi_screen_wifi_back_btn_label = lv_label_create(ui->wifi_screen_wifi_back_btn);
    lv_label_set_text(ui->wifi_screen_wifi_back_btn_label, "");
    lv_label_set_long_mode(ui->wifi_screen_wifi_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->wifi_screen_wifi_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->wifi_screen_wifi_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->wifi_screen_wifi_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->wifi_screen_wifi_back_btn, 5, 215);
    lv_obj_set_size(ui->wifi_screen_wifi_back_btn, 30, 20);

    //Write style for wifi_screen_wifi_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->wifi_screen_wifi_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_wifi_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_wifi_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_screen_wifi_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_wifi_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_wifi_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->wifi_screen_wifi_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->wifi_screen_wifi_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->wifi_screen_wifi_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_screen_wifi_back_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_wifi_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_wifi_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_wifi_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes wifi_screen_net_config_label
    ui->wifi_screen_net_config_label = lv_label_create(ui->wifi_screen_cont_1);
    lv_label_set_text(ui->wifi_screen_net_config_label, "网络配置");
    lv_label_set_long_mode(ui->wifi_screen_net_config_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->wifi_screen_net_config_label, 0, 0);
    lv_obj_set_size(ui->wifi_screen_net_config_label, 320, 20);

    //Write style for wifi_screen_net_config_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_screen_net_config_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_net_config_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_net_config_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_net_config_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_net_config_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes wifi_screen_wifi_name_label
    ui->wifi_screen_wifi_name_label = lv_label_create(ui->wifi_screen_cont_1);
    lv_label_set_text(ui->wifi_screen_wifi_name_label, "WIFI名称");
    lv_label_set_long_mode(ui->wifi_screen_wifi_name_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->wifi_screen_wifi_name_label, 5, 28);
    lv_obj_set_size(ui->wifi_screen_wifi_name_label, 70, 20);

    //Write style for wifi_screen_wifi_name_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_screen_wifi_name_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_wifi_name_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_wifi_name_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_wifi_name_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_wifi_name_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes wifi_screen_wifi_pwd_label
    ui->wifi_screen_wifi_pwd_label = lv_label_create(ui->wifi_screen_cont_1);
    lv_label_set_text(ui->wifi_screen_wifi_pwd_label, "WIFI密码");
    lv_label_set_long_mode(ui->wifi_screen_wifi_pwd_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->wifi_screen_wifi_pwd_label, 5, 68);
    lv_obj_set_size(ui->wifi_screen_wifi_pwd_label, 70, 20);

    //Write style for wifi_screen_wifi_pwd_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_screen_wifi_pwd_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_wifi_pwd_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_wifi_pwd_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_wifi_pwd_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_wifi_pwd_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes wifi_screen_pwd_textarea
    ui->wifi_screen_pwd_textarea = lv_textarea_create(ui->wifi_screen_cont_1);
    lv_textarea_set_text(ui->wifi_screen_pwd_textarea, "");
    lv_textarea_set_placeholder_text(ui->wifi_screen_pwd_textarea, "passward");
    lv_textarea_set_password_bullet(ui->wifi_screen_pwd_textarea, "*");
    lv_textarea_set_password_mode(ui->wifi_screen_pwd_textarea, true);
    lv_textarea_set_one_line(ui->wifi_screen_pwd_textarea, false);
    lv_textarea_set_accepted_chars(ui->wifi_screen_pwd_textarea, "");
    lv_textarea_set_max_length(ui->wifi_screen_pwd_textarea, 32);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->wifi_screen_pwd_textarea, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->wifi_screen_pwd_textarea, 80, 60);
    lv_obj_set_size(ui->wifi_screen_pwd_textarea, 180, 30);

    //Write style for wifi_screen_pwd_textarea, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->wifi_screen_pwd_textarea, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_pwd_textarea, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_pwd_textarea, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_screen_pwd_textarea, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_pwd_textarea, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_pwd_textarea, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_pwd_textarea, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_pwd_textarea, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_screen_pwd_textarea, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_screen_pwd_textarea, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_screen_pwd_textarea, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_screen_pwd_textarea, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_pwd_textarea, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_pwd_textarea, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_pwd_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_pwd_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_pwd_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for wifi_screen_pwd_textarea, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->wifi_screen_pwd_textarea, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_pwd_textarea, lv_color_hex(0xf2f7fb), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_pwd_textarea, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_pwd_textarea, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes wifi_screen_ssid_textarea
    ui->wifi_screen_ssid_textarea = lv_textarea_create(ui->wifi_screen_cont_1);
    lv_textarea_set_text(ui->wifi_screen_ssid_textarea, "");
    lv_textarea_set_placeholder_text(ui->wifi_screen_ssid_textarea, "ssid");
    lv_textarea_set_password_bullet(ui->wifi_screen_ssid_textarea, "*");
    lv_textarea_set_password_mode(ui->wifi_screen_ssid_textarea, false);
    lv_textarea_set_one_line(ui->wifi_screen_ssid_textarea, false);
    lv_textarea_set_accepted_chars(ui->wifi_screen_ssid_textarea, "");
    lv_textarea_set_max_length(ui->wifi_screen_ssid_textarea, 32);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->wifi_screen_ssid_textarea, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->wifi_screen_ssid_textarea, 80, 22);
    lv_obj_set_size(ui->wifi_screen_ssid_textarea, 180, 30);

    //Write style for wifi_screen_ssid_textarea, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->wifi_screen_ssid_textarea, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_ssid_textarea, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_ssid_textarea, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_screen_ssid_textarea, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_ssid_textarea, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_ssid_textarea, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_ssid_textarea, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_ssid_textarea, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_screen_ssid_textarea, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_screen_ssid_textarea, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_screen_ssid_textarea, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_screen_ssid_textarea, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_ssid_textarea, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_ssid_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_ssid_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_ssid_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_ssid_textarea, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for wifi_screen_ssid_textarea, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->wifi_screen_ssid_textarea, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_ssid_textarea, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_ssid_textarea, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_ssid_textarea, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes wifi_screen_connect_btn
    ui->wifi_screen_connect_btn = lv_btn_create(ui->wifi_screen_cont_1);
    ui->wifi_screen_connect_btn_label = lv_label_create(ui->wifi_screen_connect_btn);
    lv_label_set_text(ui->wifi_screen_connect_btn_label, "连接");
    lv_label_set_long_mode(ui->wifi_screen_connect_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->wifi_screen_connect_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->wifi_screen_connect_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->wifi_screen_connect_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->wifi_screen_connect_btn, 264, 65);
    lv_obj_set_size(ui->wifi_screen_connect_btn, 50, 20);

    //Write style for wifi_screen_connect_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->wifi_screen_connect_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_screen_connect_btn, lv_color_hex(0x5498d1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_connect_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_screen_connect_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_connect_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_connect_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_screen_connect_btn, lv_color_hex(0xffcd00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_connect_btn, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_connect_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_connect_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for wifi_screen_connect_btn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->wifi_screen_connect_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->wifi_screen_connect_btn, lv_color_hex(0x6fd01c), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->wifi_screen_connect_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->wifi_screen_connect_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->wifi_screen_connect_btn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->wifi_screen_connect_btn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->wifi_screen_connect_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->wifi_screen_connect_btn, &lv_Font_8, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->wifi_screen_connect_btn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes wifi_screen_pwd_show_imgbtn
    ui->wifi_screen_pwd_show_imgbtn = lv_imgbtn_create(ui->wifi_screen_cont_1);
    lv_obj_add_flag(ui->wifi_screen_pwd_show_imgbtn, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->wifi_screen_pwd_show_imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, "0:/PICTURE/software_icon/pwd_show.bin", NULL);
    ui->wifi_screen_pwd_show_imgbtn_label = lv_label_create(ui->wifi_screen_pwd_show_imgbtn);
    lv_label_set_text(ui->wifi_screen_pwd_show_imgbtn_label, "");
    lv_label_set_long_mode(ui->wifi_screen_pwd_show_imgbtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->wifi_screen_pwd_show_imgbtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->wifi_screen_pwd_show_imgbtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_screen_pwd_show_imgbtn, 237, 67);
    lv_obj_set_size(ui->wifi_screen_pwd_show_imgbtn, 16, 16);

    //Write style for wifi_screen_pwd_show_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->wifi_screen_pwd_show_imgbtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_pwd_show_imgbtn, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_pwd_show_imgbtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_pwd_show_imgbtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->wifi_screen_pwd_show_imgbtn, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for wifi_screen_pwd_show_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->wifi_screen_pwd_show_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->wifi_screen_pwd_show_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->wifi_screen_pwd_show_imgbtn, &lv_Font_7, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->wifi_screen_pwd_show_imgbtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for wifi_screen_pwd_show_imgbtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->wifi_screen_pwd_show_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->wifi_screen_pwd_show_imgbtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->wifi_screen_pwd_show_imgbtn, &lv_Font_7, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->wifi_screen_pwd_show_imgbtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for wifi_screen_pwd_show_imgbtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->wifi_screen_pwd_show_imgbtn, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->wifi_screen_pwd_show_imgbtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes wifi_screen_connect_status_label
    ui->wifi_screen_connect_status_label = lv_label_create(ui->wifi_screen_cont_1);
    lv_label_set_text(ui->wifi_screen_connect_status_label, "已连接");
    lv_label_set_long_mode(ui->wifi_screen_connect_status_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->wifi_screen_connect_status_label, 110, 104);
    lv_obj_set_size(ui->wifi_screen_connect_status_label, 100, 20);

    //Write style for wifi_screen_connect_status_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_screen_connect_status_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_screen_connect_status_label, &lv_Font_8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->wifi_screen_connect_status_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_screen_connect_status_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_screen_connect_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of wifi_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->wifi_screen);

    //Init events for screen.
    events_init_wifi_screen(ui);
}
