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



void setup_scr_peripheral_screen(lv_ui *ui)
{
    //Write codes peripheral_screen
    ui->peripheral_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->peripheral_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->peripheral_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for peripheral_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->peripheral_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_cont_1
    ui->peripheral_screen_cont_1 = lv_obj_create(ui->peripheral_screen);
    lv_obj_set_pos(ui->peripheral_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->peripheral_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->peripheral_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for peripheral_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->peripheral_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->peripheral_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->peripheral_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->peripheral_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->peripheral_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_spl06_label
    ui->peripheral_screen_spl06_label = lv_label_create(ui->peripheral_screen_cont_1);
    lv_label_set_text(ui->peripheral_screen_spl06_label, "spl06:");
    lv_label_set_long_mode(ui->peripheral_screen_spl06_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->peripheral_screen_spl06_label, 15, 30);
    lv_obj_set_size(ui->peripheral_screen_spl06_label, 300, 20);

    //Write style for peripheral_screen_spl06_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_spl06_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_spl06_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_spl06_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_spl06_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_spl06_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_lis2dh12tr_label
    ui->peripheral_screen_lis2dh12tr_label = lv_label_create(ui->peripheral_screen_cont_1);
    lv_label_set_text(ui->peripheral_screen_lis2dh12tr_label, "Lis2dh12tr:");
    lv_label_set_long_mode(ui->peripheral_screen_lis2dh12tr_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->peripheral_screen_lis2dh12tr_label, 15, 60);
    lv_obj_set_size(ui->peripheral_screen_lis2dh12tr_label, 300, 20);

    //Write style for peripheral_screen_lis2dh12tr_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_lis2dh12tr_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_lis2dh12tr_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_lis2dh12tr_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_lis2dh12tr_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_lis2dh12tr_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_bh1750_label
    ui->peripheral_screen_bh1750_label = lv_label_create(ui->peripheral_screen_cont_1);
    lv_label_set_text(ui->peripheral_screen_bh1750_label, "bh1750:");
    lv_label_set_long_mode(ui->peripheral_screen_bh1750_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->peripheral_screen_bh1750_label, 15, 90);
    lv_obj_set_size(ui->peripheral_screen_bh1750_label, 300, 20);

    //Write style for peripheral_screen_bh1750_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_bh1750_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_bh1750_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_bh1750_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_bh1750_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_bh1750_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_sht30_label
    ui->peripheral_screen_sht30_label = lv_label_create(ui->peripheral_screen_cont_1);
    lv_label_set_text(ui->peripheral_screen_sht30_label, "sht30:");
    lv_label_set_long_mode(ui->peripheral_screen_sht30_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->peripheral_screen_sht30_label, 15, 120);
    lv_obj_set_size(ui->peripheral_screen_sht30_label, 300, 20);

    //Write style for peripheral_screen_sht30_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_sht30_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_sht30_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_sht30_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_sht30_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_sht30_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_peripheral_back_btn
    ui->peripheral_screen_peripheral_back_btn = lv_btn_create(ui->peripheral_screen_cont_1);
    ui->peripheral_screen_peripheral_back_btn_label = lv_label_create(ui->peripheral_screen_peripheral_back_btn);
    lv_label_set_text(ui->peripheral_screen_peripheral_back_btn_label, "");
    lv_label_set_long_mode(ui->peripheral_screen_peripheral_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->peripheral_screen_peripheral_back_btn_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->peripheral_screen_peripheral_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->peripheral_screen_peripheral_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->peripheral_screen_peripheral_back_btn, 5, 215);
    lv_obj_set_size(ui->peripheral_screen_peripheral_back_btn, 30, 20);

    //Write style for peripheral_screen_peripheral_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->peripheral_screen_peripheral_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->peripheral_screen_peripheral_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->peripheral_screen_peripheral_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->peripheral_screen_peripheral_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_peripheral_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_peripheral_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->peripheral_screen_peripheral_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->peripheral_screen_peripheral_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->peripheral_screen_peripheral_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_peripheral_back_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_peripheral_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_peripheral_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_peripheral_back_btn, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_peripheral_title_label
    ui->peripheral_screen_peripheral_title_label = lv_label_create(ui->peripheral_screen_cont_1);
    lv_label_set_text(ui->peripheral_screen_peripheral_title_label, "外设");
    lv_label_set_long_mode(ui->peripheral_screen_peripheral_title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->peripheral_screen_peripheral_title_label, 5, 5);
    lv_obj_set_size(ui->peripheral_screen_peripheral_title_label, 35, 15);

    //Write style for peripheral_screen_peripheral_title_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_peripheral_title_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_peripheral_title_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_peripheral_title_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_peripheral_title_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_peripheral_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes peripheral_screen_atgm332d_label
    ui->peripheral_screen_atgm332d_label = lv_label_create(ui->peripheral_screen_cont_1);
    lv_label_set_text(ui->peripheral_screen_atgm332d_label, "atgm332d:");
    lv_label_set_long_mode(ui->peripheral_screen_atgm332d_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->peripheral_screen_atgm332d_label, 15, 150);
    lv_obj_set_size(ui->peripheral_screen_atgm332d_label, 300, 20);

    //Write style for peripheral_screen_atgm332d_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->peripheral_screen_atgm332d_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->peripheral_screen_atgm332d_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->peripheral_screen_atgm332d_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->peripheral_screen_atgm332d_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->peripheral_screen_atgm332d_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of peripheral_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->peripheral_screen);

    //Init events for screen.
    events_init_peripheral_screen(ui);
}
