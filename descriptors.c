/***************************************************************************//**
 * @file descriptors.c
 * @brief USB descriptors for HID mouse example project.
 * @version 3.20.10
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#include "descriptors.h"

EFM32_ALIGN(4)
const USB_DeviceDescriptor_TypeDef USBDESC_deviceDesc __attribute__ ((aligned(4)))=
{
  .bLength            = USB_DEVICE_DESCSIZE,
  .bDescriptorType    = USB_DEVICE_DESCRIPTOR,
  .bcdUSB             = 0x0200,
  .bDeviceClass       = 0,
  .bDeviceSubClass    = 0,
  .bDeviceProtocol    = 0,
  .bMaxPacketSize0    = USB_FS_CTRL_EP_MAXSIZE,
  .idVendor           = 0x10C4,
  .idProduct          = 0x0002,
  .bcdDevice          = 0x0000,
  .iManufacturer      = 1,
  .iProduct           = 2,
  .iSerialNumber      = 3,
  .bNumConfigurations = 1
};

EFM32_ALIGN(4)
const uint8_t USBDESC_configDesc[] __attribute__ ((aligned(4)))=
{
  /*** Configuration descriptor ***/
  USB_CONFIG_DESCSIZE,    /* bLength                                   */
  USB_CONFIG_DESCRIPTOR,  /* bDescriptorType                           */

  USB_CONFIG_DESCSIZE +   /* wTotalLength (LSB)                        */
  USB_INTERFACE_DESCSIZE +
  USB_HID_DESCSIZE +
  (USB_ENDPOINT_DESCSIZE * NUM_EP_USED),

  (USB_CONFIG_DESCSIZE +  /* wTotalLength (MSB)                        */
  USB_INTERFACE_DESCSIZE +
  USB_HID_DESCSIZE +
  (USB_ENDPOINT_DESCSIZE * NUM_EP_USED))>>8,

  1,                      /* bNumInterfaces                            */
  1,                      /* bConfigurationValue                       */
  0,                      /* iConfiguration                            */

#if defined(BUSPOWERED)
  CONFIG_DESC_BM_RESERVED_D7,    /* bmAttrib: Bus powered              */
#else
  CONFIG_DESC_BM_RESERVED_D7 |   /* bmAttrib: Self powered             */
  CONFIG_DESC_BM_SELFPOWERED,
#endif

  CONFIG_DESC_MAXPOWER_mA( 100 ), /* bMaxPower: 100 mA                 */

  /*** Interface descriptor ***/
  USB_INTERFACE_DESCSIZE, /* bLength               */
  USB_INTERFACE_DESCRIPTOR,/* bDescriptorType      */
  HIDKBD_INTERFACE_NO,    /* bInterfaceNumber      */
  0,                      /* bAlternateSetting     */
  NUM_EP_USED,            /* bNumEndpoints         */
  0x03,                   /* bInterfaceClass (HID) */
  0,                      /* bInterfaceSubClass    */
  USB_CLASS_HID_MOUSE,    /* bInterfaceProtocol    */
  0,                      /* iInterface            */

  /*** HID descriptor ***/
  USB_HID_DESCSIZE,       /* bLength               */
  USB_HID_DESCRIPTOR,     /* bDescriptorType       */
  0x11,                   /* bcdHID (LSB)          */
  0x01,                   /* bcdHID (MSB)          */
  0,                      /* bCountryCode          */
  1,                      /* bNumDescriptors       */
  USB_HID_REPORT_DESCRIPTOR,            /* bDecriptorType        */
  sizeof( HIDKBD_MouseReportDescriptor ),    /* wDescriptorLength(LSB)*/
  sizeof( HIDKBD_MouseReportDescriptor )>>8, /* wDescriptorLength(MSB)*/

  /*** Endpoint descriptor ***/
  USB_ENDPOINT_DESCSIZE,  /* bLength               */
  USB_ENDPOINT_DESCRIPTOR,/* bDescriptorType       */
  HIDKBD_INTR_IN_EP_ADDR, /* bEndpointAddress (IN) */
  USB_EPTYPE_INTR,        /* bmAttributes          */
  USB_FS_INTR_EP_MAXSIZE, /* wMaxPacketSize (LSB)  */
  0,                      /* wMaxPacketSize (MSB)  */
  HIDKBD_POLL_RATE,       /* bInterval             */
};

const void *USBDESC_HidDescriptor = (void*)
  &USBDESC_configDesc[ USB_CONFIG_DESCSIZE + USB_INTERFACE_DESCSIZE ];

STATIC_CONST_STRING_DESC_LANGID( langID, 0x04, 0x09 );
STATIC_CONST_STRING_DESC( iManufacturer, 'S','i','l','i','c','o','n',' ','L', \
                                         'a','b','o','r','a','t','o','r','i', \
                                         'e','s',' ','I','n','c','.' );
STATIC_CONST_STRING_DESC( iProduct     , 'E','F','M','3','2',' ','H','a','p', \
                                         'p','y',' ','G','e','c','k','o',' ', \
                                         'U','S','B',' ','H','I','D',' ','M', \
                                         'o','u','s','e' );
STATIC_CONST_STRING_DESC( iSerialNumber, '0','0','0','0','0','0',             \
                                         '0','0','1','3','3','7' );

const void * const USBDESC_strings[] =
{
  &langID,
  &iManufacturer,
  &iProduct,
  &iSerialNumber
};

/* Endpoint buffer sizes */
/* 1 = single buffer, 2 = double buffering, 3 = triple buffering ... */
const uint8_t USBDESC_bufferingMultiplier[ NUM_EP_USED + 1 ] = { 1, 1 };

EFM32_ALIGN(4)
const HIDKBD_MouseReport_t USBDESC_noMouseReport =
{ 0x00, 0x00, 0x00 };

EFM32_ALIGN(4)
const HIDKBD_MouseReport_t USBDESC_leftMouseReport =
{ 0x01, 0x00, 0x00 };

EFM32_ALIGN(4)
const HIDKBD_MouseReport_t USBDESC_rightMouseReport =
{ 0x02, 0x00, 0x00 };