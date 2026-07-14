#include "lvgl.h"

/**
 * @brief  获取文件位置
 * @param  fd：文件描述符
 * @return 当前位置
 */
long lv_tell(lv_fs_file_t *fd)
{
    uint32_t pos = 0;
    lv_fs_tell(fd, &pos);
    return pos;
}

/**
 * @brief  文件系统测试
 * @param  无
 * @return 无
 */
static void lv_fs_test(void)
{
    char rbuf[30] = {0};
    uint32_t rsize = 0;
    lv_fs_file_t fd;
    lv_fs_res_t res;

    res = lv_fs_open(&fd, "0:/LV_FATFS/test.txt", LV_FS_MODE_RD);
    
    if (res != LV_FS_RES_OK)
    {
        lv_obj_t *error_label = lv_label_create(lv_scr_act());
        lv_label_set_text(error_label, "Open 0:/LV_FATFS/test.txt ERROR");
        lv_obj_align(error_label, LV_ALIGN_CENTER, 0, 40);
        return;
    }
    
    lv_tell(&fd);

    lv_fs_seek(&fd, 0,LV_FS_SEEK_SET);
    lv_tell(&fd);

    res = lv_fs_read(&fd, rbuf, 100, &rsize);
    
    if (res != LV_FS_RES_OK)
    {
        lv_obj_t *error_label = lv_label_create(lv_scr_act());
        lv_label_set_text(error_label, "Read ERROR");
        lv_obj_align(error_label, LV_ALIGN_CENTER, 0, 60);
        lv_fs_close(&fd);
        return ;
    }
    
    lv_tell(&fd);
    rbuf[rsize] = '\0'; // 添加字符串结束符
    
    // 显示LVGL读取文件内容
    lv_obj_t *content_label = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(content_label, "File Content: %s", rbuf);
    lv_obj_align(content_label, LV_ALIGN_CENTER, 0, 80);

    lv_fs_close(&fd); 
}

/**
 * @brief  显示 SD 卡中的图片
 * @param  无
 * @return 无
 */
static void lv_show_image(void)
{
    // 创建图像对象
    lv_obj_t *img = lv_img_create(lv_scr_act());
    
    // 设置图像源为 SD 卡中的 .bin 文件
    lv_img_set_src(img, "0:/PICTURE/peripheral_icon.bin");
    
    // 居中显示
    lv_obj_center(img);
    
    // 可选：添加错误处理
    if (lv_img_get_src(img) == NULL) {
        lv_obj_t *label = lv_label_create(lv_scr_act());
        lv_label_set_text(label, "Failed to load image!");
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 40);
    }
}

/**
 * @brief  文件系统测试
 * @param  无
 * @return 无
 */
void lv_mainstart(void)
{
//    lv_obj_t *label = lv_label_create(lv_scr_act());
//    lv_label_set_text(label, "FATFS TEST");
//    lv_obj_center(label);
//    lv_fs_test();
	lv_show_image();
}