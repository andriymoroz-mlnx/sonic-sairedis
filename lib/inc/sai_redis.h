#ifndef __SAI_REDIS__
#define __SAI_REDIS__

#include <mutex>
#include <set>
#include <unordered_map>

#include <stdio.h>

extern "C" {
#include "sai.h"
}

#include "swss/redisclient.h"
#include "swss/dbconnector.h"
#include "swss/producertable.h"
#include "swss/consumertable.h"
#include "swss/notificationconsumer.h"
#include "swss/notificationproducer.h"
#include "swss/table.h"
#include "swss/select.h"
#include "swss/logger.h"
#include "meta/sai_meta.h"

// if we don't receive response from syncd in 6*60 seconds
// there is something wrong and we should fail
#define GET_RESPONSE_TIMEOUT (6*60*1000)

extern volatile bool                    g_record;
extern void setRecording(bool record);
extern sai_status_t setRecordingOutputDir(
        _In_ const sai_attribute_t &attr);
extern void recordLine(std::string s);

extern std::string joinFieldValues(
        _In_ const std::vector<swss::FieldValueTuple> &values);

extern volatile bool                    g_useTempView;

// other global declarations

extern service_method_table_t           g_services;
extern swss::DBConnector               *g_db;
extern swss::ProducerTable             *g_asicState;

extern swss::ConsumerTable             *g_redisGetConsumer;
extern swss::NotificationConsumer      *g_redisNotifications;

extern swss::RedisClient               *g_redisClient;

extern std::mutex g_apimutex;

extern const sai_acl_api_t              redis_acl_api;
extern const sai_buffer_api_t           redis_buffer_api;
extern const sai_fdb_api_t              redis_fdb_api;
extern const sai_hash_api_t             redis_hash_api;
extern const sai_hostif_api_t           redis_host_interface_api;
extern const sai_lag_api_t              redis_lag_api;
extern const sai_mirror_api_t           redis_mirror_api;
extern const sai_neighbor_api_t         redis_neighbor_api;
extern const sai_next_hop_api_t         redis_next_hop_api;
extern const sai_next_hop_group_api_t   redis_next_hop_group_api;
extern const sai_policer_api_t          redis_policer_api;
extern const sai_port_api_t             redis_port_api;
extern const sai_qos_map_api_t          redis_qos_map_api;
extern const sai_queue_api_t            redis_queue_api;
extern const sai_route_api_t            redis_route_api;
extern const sai_router_interface_api_t redis_router_interface_api;
extern const sai_samplepacket_api_t     redis_samplepacket_api;
extern const sai_scheduler_api_t        redis_scheduler_api;
extern const sai_scheduler_group_api_t  redis_scheduler_group_api;
extern const sai_stp_api_t              redis_stp_api;
extern const sai_switch_api_t           redis_switch_api;
extern const sai_tunnel_api_t           redis_tunnel_api;
extern const sai_udf_api_t              redis_udf_api;
extern const sai_virtual_router_api_t   redis_router_api;
extern const sai_vlan_api_t             redis_vlan_api;
extern const sai_wred_api_t             redis_wred_api;

extern sai_switch_notification_t redis_switch_notifications;

#define UNREFERENCED_PARAMETER(X)

bool redis_validate_contains_attribute(
    _In_ sai_attr_id_t required_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list);

const sai_attribute_t* redis_get_attribute_by_id(
    _In_ sai_attr_id_t id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list);

sai_object_id_t redis_create_virtual_object_id(
        _In_ sai_object_type_t object_type);

void translate_rid_to_vid(
        _In_ sai_object_type_t object_type,
        _In_ uint32_t attr_count,
        _In_ sai_attribute_t *attr_list);

// separate methods are needed for vlan to not confuse with object_id

// CREATE

sai_status_t redis_generic_create(
        _In_ sai_object_type_t object_type,
        _Out_ sai_object_id_t* object_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

sai_status_t redis_generic_create_fdb_entry(
        _In_ const sai_fdb_entry_t *fdb_entry,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

sai_status_t redis_generic_create_neighbor_entry(
        _In_ const sai_neighbor_entry_t* neighbor_entry,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

sai_status_t redis_generic_create_route_entry(
        _In_ const sai_unicast_route_entry_t* unicast_route_entry,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

sai_status_t redis_generic_create_vlan(
        _In_ sai_vlan_id_t vlan_id);

// REMOVE

sai_status_t redis_generic_remove(
        _In_ sai_object_type_t object_type,
        _In_ sai_object_id_t object_id);

sai_status_t redis_generic_remove_fdb_entry(
        _In_ const sai_fdb_entry_t* fdb_entry);

sai_status_t redis_generic_remove_neighbor_entry(
        _In_ const sai_neighbor_entry_t* neighbor_entry);

sai_status_t redis_generic_remove_route_entry(
        _In_ const sai_unicast_route_entry_t* unicast_route_entry);

sai_status_t redis_generic_remove_vlan(
        _In_ sai_vlan_id_t vlan_id);

// SET

sai_status_t redis_generic_set(
        _In_ sai_object_type_t object_type,
        _In_ sai_object_id_t object_id,
        _In_ const sai_attribute_t *attr);

sai_status_t redis_generic_set_fdb_entry(
        _In_ const sai_fdb_entry_t *fdb_entry,
        _In_ const sai_attribute_t *attr);

sai_status_t redis_generic_set_neighbor_entry(
        _In_ const sai_neighbor_entry_t* neighbor_entry,
        _In_ const sai_attribute_t *attr);

sai_status_t redis_generic_set_route_entry(
        _In_ const sai_unicast_route_entry_t* unicast_route_entry,
        _In_ const sai_attribute_t *attr);

sai_status_t redis_generic_set_vlan(
        _In_ sai_vlan_id_t vlan_id,
        _In_ const sai_attribute_t *attr);

sai_status_t redis_generic_set_trap(
        _In_ sai_hostif_trap_id_t hostif_trapid,
        _In_ const sai_attribute_t *attr);

sai_status_t redis_generic_set_switch(
        _In_ const sai_attribute_t *attr);

sai_status_t internal_redis_bulk_generic_set(
        _In_ sai_object_type_t object_type,
        _In_ const std::vector<std::string> &serialized_object_ids,
        _In_ const sai_attribute_t *attr_list,
        _In_ const sai_status_t *object_statuses);

// GET

sai_status_t redis_generic_get(
        _In_ sai_object_type_t object_type,
        _In_ sai_object_id_t object_id,
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

sai_status_t redis_generic_get_fdb_entry(
        _In_ const sai_fdb_entry_t *fdb_entry,
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

sai_status_t redis_generic_get_neighbor_entry(
        _In_ const sai_neighbor_entry_t* neighbor_entry,
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

sai_status_t redis_generic_get_route_entry(
        _In_ const sai_unicast_route_entry_t* unicast_route_entry,
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

sai_status_t redis_generic_get_vlan(
        _In_ sai_vlan_id_t vlan_id,
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

sai_status_t redis_generic_get_trap(
        _In_ sai_hostif_trap_id_t hostif_trapid,
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

sai_status_t redis_generic_get_switch(
        _In_ uint32_t attr_count,
        _Out_ sai_attribute_t *attr_list);

// notifications

void handle_notification(
        _In_ const std::string &notification,
        _In_ const std::string &data,
        _In_ const std::vector<swss::FieldValueTuple> &values);

#endif // __SAI_REDIS__
