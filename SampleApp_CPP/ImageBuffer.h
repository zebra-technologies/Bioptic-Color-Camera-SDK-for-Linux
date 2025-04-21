/***************************************************************
 * Name:      ImageBuffer.h
 * Purpose:   Defines implementation of image frame handling
 * Author:     ()
 * Created:   2021-03-023
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#ifndef CAMERA_VIDEO_H_
#define CAMERA_VIDEO_H_

#include <wx/wx.h>

#include <mutex>

/*
    Image buffer class to manage the image frames.
*/
class ImageBuffer
{
public:
    ImageBuffer();
    ~ImageBuffer();

    /**
    * Method to Allocate image buffer 
    * @param image_frame_width & image_frame_height
    * @return void function
    */
    void AllocateBuffer(uint32_t width, uint32_t height);

    /**
    * Method to copy image frame data to image buffer
    * @param image data and data size
    * @return void function
    */
    void CopyToBuffer(const uint8_t *data, size_t size);

    /**
    * Method to copy image frame data from image buffer
    * @param image data and data size
    * @return void function
    */
    void CopyFromBuffer(uint8_t *data, size_t& size);

    /**
    * Method to save an image in Jpeg format
    * @param image name in .jpg format
    * @return void function
    */
    void SaveAsJpeg(std::string filename);

    /**
    * Method to save an image in Bmp format
    * @param image name in .bmp format
    * @return void function
    */
    void SaveAsBmp(std::string filename);

private:
    std::mutex mutex_;

    size_t utilized_size_ = 0;  // This is the amount we currently use.
    size_t image_size_ = 0; // Capacity.
    uint8_t *image_frame_data_ = nullptr;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

#endif // CAMERA_VIDEO_H_
