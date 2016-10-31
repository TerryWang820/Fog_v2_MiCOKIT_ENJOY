#ifndef _FOG_V2_FOG_V2_INCLUDE_H_
#define _FOG_V2_FOG_V2_INCLUDE_H_

#include "mico.h"
#include "fog_v2_config.h"

#include "./fog_bonjour/fog_bonjour.h"

#include "./fog_http/fog_http_client.h"
#include "./fog_http/fog_v2_sub.h"
#include "./fog_http/fog_v2_sub_device_management.h"
#include "./fog_http/fog_v2.h"

#include "./fog_mqtt/fog_mqtt.h"
#include "./fog_mqtt/fog_process_mqtt_cmd.h"

#include "./fog_ota/fog_ota.h"

#include "./fog_tcp_server/fog_tcp_server.h"


//-------用户调用接口-------
//功能：开启fog的服务
//参数：无
//返回值：kNoErr为成功
OSStatus start_fog_v2_service(void);

//功能：往云端发送数据
//参数： payload - 要往云端发送的数据，该指针指向的数据只能为json格式
//参数： flag - 发送方式
//下面三个宏定义组合,采用异或组合的方式
//FOG_V2_SEND_EVENT_RULES_PUBLISH  向设备的topic去publish数据
//FOG_V2_SEND_EVENT_RULES_DATEBASE 将此次的payload数据存入数据库
//FOG_V2_SEND_EVENT_RULES_PRODUCT  向设备对应产品的topic去publish数据(数据推送给厂商)
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_device_send_event(const char *payload, uint32_t flag);

//功能：从云端接收数据
//参数： payload - 接收数据缓冲区地址
//参数： payload_len - 接收数据缓冲区地址的长度
//参数： timeout - 接收数据等待时间
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_device_recv_command(char *payload, uint32_t payload_len, uint32_t timeout);

//功能：设备端设置回收标志位 若调用该接口，设备重启后联网会自动向云端发起设备回收请求
//参数：无
//返回值：无
void fog_v2_set_device_recovery_flag(void);

//功能：查询本设备是否有超级用户（被绑定)
//参数：无
//返回值：true - 有超级用户，flase - 无超级用户
bool fog_v2_is_have_superuser(void);


#if (FOG_V2_USE_SUB_DEVICE == 1)
//-------子设备相关接口-------
//注意：要开启网关子设备API,则需要在应用程序config/fog_v2_config.h中 FOG_V2_USE_SUB_DEVICE 宏定义更改为
//#define FOG_V2_USE_SUB_DEVICE  (1)才能生效。

//功能：添加一个子设备
//参数： s_product_id - 子设备产品ID
//参数： s_mac - 子设备MAC地址
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_add_subdevice( const char *s_product_id, const char *s_mac, bool auto_set_online);

//功能：删除一个子设备
//参数： s_product_id - 子设备产品ID
//参数： s_mac - 子设备MAC地址
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_remove_subdevice( const char *s_product_id, const char *s_mac );

//功能：设置子设备在线离线状态
//参数： s_product_id - 子设备产品ID
//参数： s_mac - 子设备MAC地址
//参数：online - 子设备是否在线
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_set_subdevice_status(const char *s_product_id, const char *s_mac, bool online);

//功能：子设备发送数据
//参数： s_product_id - 子设备产品ID
//参数： s_mac - 子设备MAC地址
//参数： flag - 发送方式
//下面两个宏定义组合,采用异或组合的方式
//FOG_V2_SEND_EVENT_RULES_PUBLISH  向设备的topic去publish数据
//FOG_V2_SEND_EVENT_RULES_DATEBASE 将此次的payload数据存入数据库
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_subdevice_send(const char *s_product_id, const char *s_mac, const char *payload, uint32_t flag);

//功能：子设备接收数据
//参数： s_product_id - 子设备产品ID
//参数： s_mac - 子设备MAC地址
//参数： payload - 接收数据缓冲区地址
//参数： payload_len - 接收数据缓冲区地址的长度
//参数： timeout - 接收数据的超时时间
//返回值：kNoErr为成功 其他值为失败
OSStatus fog_v2_subdevice_recv(const char *s_product_id, const char *s_mac, char *payload, uint32_t payload_len, uint32_t timeout);

//功能：设备状态改变通知（该函数需要用户在自己的代码中复写函数体，中间件是使用WEAK定义调用该函数）
//参数：type - 事件类型
//事件类型一共有三种
//MQTT_CMD_GATEWAY_UNBIND   网关设备被解绑(s_product_id和s_mac无效)
//MQTT_CMD_GATEWAY_BIND     网关设备被绑定(s_product_id和s_mac无效)
//参数： s_product_id - 子设备产品ID
//参数： s_mac - 子设备MAC地址
//返回值：无
//USED void user_fog_v2_device_notification(SUBDEVICE_CMD_TYPE type, const char *s_product_id, const char *s_mac)
//{
//    //user todo....
//}

#endif //end of FOG_V2_USE_SUB_DEVICE

#endif
