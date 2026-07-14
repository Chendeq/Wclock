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



void setup_scr_setting_screen(lv_ui *ui)
{
    //Write codes setting_screen
    ui->setting_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->setting_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->setting_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_1
    ui->setting_screen_cont_1 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->setting_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_setting_back_btn
    ui->setting_screen_setting_back_btn = lv_btn_create(ui->setting_screen_cont_1);
    ui->setting_screen_setting_back_btn_label = lv_label_create(ui->setting_screen_setting_back_btn);
    lv_label_set_text(ui->setting_screen_setting_back_btn_label, "");
    lv_label_set_long_mode(ui->setting_screen_setting_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->setting_screen_setting_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->setting_screen_setting_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->setting_screen_setting_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->setting_screen_setting_back_btn, 5, 215);
    lv_obj_set_size(ui->setting_screen_setting_back_btn, 30, 20);

    //Write style for setting_screen_setting_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_screen_setting_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_setting_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_setting_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_setting_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_setting_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_setting_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->setting_screen_setting_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->setting_screen_setting_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->setting_screen_setting_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_setting_back_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_setting_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_setting_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_setting_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_setting_title_label
    ui->setting_screen_setting_title_label = lv_label_create(ui->setting_screen_cont_1);
    lv_label_set_text(ui->setting_screen_setting_title_label, "设置");
    lv_label_set_long_mode(ui->setting_screen_setting_title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_setting_title_label, 5, 5);
    lv_obj_set_size(ui->setting_screen_setting_title_label, 40, 20);

    //Write style for setting_screen_setting_title_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_setting_title_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_setting_title_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_setting_title_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_setting_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_setting_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_setting_list
    ui->setting_screen_setting_list = lv_list_create(ui->setting_screen_cont_1);
    ui->setting_screen_setting_list_item0 = lv_list_add_btn(ui->setting_screen_setting_list, "0:/PICTURE/software_icon/wifi_icon.bin", "WLAN");
    ui->setting_screen_setting_list_item1 = lv_list_add_btn(ui->setting_screen_setting_list, "0:/PICTURE/software_icon/bluetooth_icon.bin", "蓝牙");
    ui->setting_screen_setting_list_item2 = lv_list_add_btn(ui->setting_screen_setting_list, "0:/PICTURE/software_icon/alarm_icon.bin", "闹钟");
    lv_obj_set_pos(ui->setting_screen_setting_list, 10, 35);
    lv_obj_set_size(ui->setting_screen_setting_list, 300, 170);
    lv_obj_set_scrollbar_mode(ui->setting_screen_setting_list, LV_SCROLLBAR_MODE_ON);

    //Write style state: LV_STATE_DEFAULT for &style_setting_screen_setting_list_main_main_default
    static lv_style_t style_setting_screen_setting_list_main_main_default;
    ui_init_style(&style_setting_screen_setting_list_main_main_default);

    lv_style_set_pad_top(&style_setting_screen_setting_list_main_main_default, 5);
    lv_style_set_pad_left(&style_setting_screen_setting_list_main_main_default, 5);
    lv_style_set_pad_right(&style_setting_screen_setting_list_main_main_default, 5);
    lv_style_set_pad_bottom(&style_setting_screen_setting_list_main_main_default, 5);
    lv_style_set_bg_opa(&style_setting_screen_setting_list_main_main_default, 255);
    lv_style_set_bg_color(&style_setting_screen_setting_list_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_setting_screen_setting_list_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_setting_screen_setting_list_main_main_default, 1);
    lv_style_set_border_opa(&style_setting_screen_setting_list_main_main_default, 255);
    lv_style_set_border_color(&style_setting_screen_setting_list_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_setting_screen_setting_list_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_setting_screen_setting_list_main_main_default, 3);
    lv_style_set_shadow_width(&style_setting_screen_setting_list_main_main_default, 0);
    lv_obj_add_style(ui->setting_screen_setting_list, &style_setting_screen_setting_list_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_screen_setting_list_main_scrollbar_default
    static lv_style_t style_setting_screen_setting_list_main_scrollbar_default;
    ui_init_style(&style_setting_screen_setting_list_main_scrollbar_default);

    lv_style_set_radius(&style_setting_screen_setting_list_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_setting_screen_setting_list_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_setting_screen_setting_list_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_setting_screen_setting_list_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->setting_screen_setting_list, &style_setting_screen_setting_list_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_screen_setting_list_extra_btns_main_default
    static lv_style_t style_setting_screen_setting_list_extra_btns_main_default;
    ui_init_style(&style_setting_screen_setting_list_extra_btns_main_default);

    lv_style_set_pad_top(&style_setting_screen_setting_list_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_setting_screen_setting_list_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_setting_screen_setting_list_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_setting_screen_setting_list_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_setting_screen_setting_list_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_setting_screen_setting_list_extra_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_setting_screen_setting_list_extra_btns_main_default, &lv_Font_10);
    lv_style_set_text_opa(&style_setting_screen_setting_list_extra_btns_main_default, 255);
    lv_style_set_radius(&style_setting_screen_setting_list_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_setting_screen_setting_list_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_setting_screen_setting_list_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_setting_screen_setting_list_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->setting_screen_setting_list_item2, &style_setting_screen_setting_list_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->setting_screen_setting_list_item1, &style_setting_screen_setting_list_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->setting_screen_setting_list_item0, &style_setting_screen_setting_list_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_screen_setting_list_extra_texts_main_default
    static lv_style_t style_setting_screen_setting_list_extra_texts_main_default;
    ui_init_style(&style_setting_screen_setting_list_extra_texts_main_default);

    lv_style_set_pad_top(&style_setting_screen_setting_list_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_setting_screen_setting_list_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_setting_screen_setting_list_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_setting_screen_setting_list_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_setting_screen_setting_list_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_setting_screen_setting_list_extra_texts_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_setting_screen_setting_list_extra_texts_main_default, &lv_Font_12);
    lv_style_set_text_opa(&style_setting_screen_setting_list_extra_texts_main_default, 255);
    lv_style_set_radius(&style_setting_screen_setting_list_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_setting_screen_setting_list_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_setting_screen_setting_list_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_setting_screen_setting_list_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_setting_screen_setting_list_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //The custom code of setting_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->setting_screen);

    //Init events for screen.
    events_init_setting_screen(ui);
}
