#pragma once
#include <stratosphere.hpp>

namespace ams::mitm
{
    struct DLogConfig
    {
        struct
        {
            bool enable_mitm;
            struct
            {
                bool disable_getstate;
                bool disable_getnetworkinfo;
                bool disable_getipv4address;
                bool disable_getdisconnectreason;
                bool disable_getsecurityparameter;
                bool disable_getnetworkconfig;
                bool disable_attachstatechangeevent;
                bool disable_getnetworkinfolatestupdate;
                bool disable_scan;
                bool disable_scanprivate;
                bool disable_setwirelesscontrollerrestriction;
                bool disable_setbluetoothaudiodeviceconnectablemode;
                bool disable_openaccesspoint;
                bool disable_closeaccesspoint;
                bool disable_createnetwork;
                bool disable_createnetworkprivate;
                bool disable_destroynetwork;
                bool disable_reject;
                bool disable_setadvertisedata;
                bool disable_setstationacceptpolicy;
                bool disable_addacceptfilterentry;
                bool disable_clearacceptfilter;
                bool disable_openstation;
                bool disable_closestation;
                bool disable_connect;
                bool disable_connectprivate;
                bool disable_disconnect;
                bool disable_initialize;
                bool disable_finalize;
                bool disable_initialize2;
            } commands;
        } ldn_u;

        struct
        {
            bool enable_mitm;
            struct
            {
                bool disable_openmode;
                bool disable_closemode;
                bool disable_getmacaddress;
                bool disable_createbss;
                bool disable_destroybss;
                bool disable_startscan;
                bool disable_stopscan;
                bool disable_connect;
                bool disable_cancelconnect;
                bool disable_join;
                bool disable_canceljoin;
                bool disable_disconnect;
                bool disable_setbeaconlostcount;
                bool disable_getsystemevent;
                bool disable_getconnectionstatus;
                bool disable_getclientstatus;
                bool disable_getbssindicationevent;
                bool disable_getbssindicationinfo;
                bool disable_getstate;
                bool disable_getallowedchannels;
                bool disable_addie;
                bool disable_deleteie;
                bool disable_putframeraw;
                bool disable_cancelgetframe;
                bool disable_createrxentry;
                bool disable_deleterxentry;
                bool disable_addethertypetorxentry;
                bool disable_deleteethertypefromrxentry;
                bool disable_addmatchingdatatorxentry;
                bool disable_removematchingdatafromrxentry;
                bool disable_getscanresult;
                bool disable_putactionframeoneshot;
                bool disable_setactionframewithbeacon;
                bool disable_cancelactionframewithbeacon;
                bool disable_createrxentryforactionframe;
                bool disable_deleterxentryforactionframe;
                bool disable_addsubtypetorxentryforactionframe;
                bool disable_deletesubtypefromrxentryforactionframe;
                bool disable_cancelgetactionframe;
                bool disable_getrssi;
                bool disable_setmaxassociationnumber;
                bool disable_cmd41;
                bool disable_cmd42;
                bool disable_cmd43;
                bool disable_cmd44;
                bool disable_cmd45;
                bool disable_cmd46;
                bool disable_cmd47;
                bool disable_cmd48;
                bool disable_cmd49;
                bool disable_cmd50;
                bool disable_cmd51;
            } commands;
        } wlan_lcl;
    };

    Result ReadConfig();
    DLogConfig *GetConfigInstance();
}
