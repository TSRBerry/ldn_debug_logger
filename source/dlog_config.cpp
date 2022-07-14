#include "logging.hpp"
#include "dlog_config.hpp"

namespace ams::mitm
{
    namespace
    {
        constexpr const char *config_path = "sdmc:/config/ldn_debug_logger/dlog.ini";
        DLogConfig g_config = {.ldn_u = {.enable_mitm = true}, .wlan_lcl = {.enable_mitm = true}};
    }

    void LogDisabledCommand(const char *service, const char *cmd)
    {
        DEBUG_LOG("CONFIG> [%s] Disabled cmd: '%s'", service, cmd);
    }

    void HandleLdnUCmdsConfig(const char *cmd, const char *value, DLogConfig *config)
    {
        constexpr const char *service = "ldn:u";
        constexpr const char *cmds[] = {"disable_getstate", "disable_getnetworkinfo", "disable_getipv4address", "disable_getdisconnectreason", "disable_getsecurityparameter", "disable_getnetworkconfig", "disable_attachstatechangeevent", "disable_getnetworkinfolatestupdate", "disable_scan", "disable_scanprivate", "disable_setwirelesscontrollerrestriction", "disable_setbluetoothaudiodeviceconnectablemode", "disable_openaccesspoint", "disable_closeaccesspoint", "disable_createnetwork", "disable_createnetworkprivate", "disable_destroynetwork", "disable_reject", "disable_setadvertisedata", "disable_setstationacceptpolicy", "disable_addacceptfilterentry", "disable_clearacceptfilter", "disable_openstation", "disable_closestation", "disable_connect", "disable_connectprivate", "disable_disconnect", "disable_initialize", "disable_finalize", "disable_initialize2"};

        for (int i = 0; i < 30; i++)
        {
            if (strcasecmp(cmd, cmds[i]) == 0 && strcasecmp(value, "1") == 0)
            {
                LogDisabledCommand(service, cmds[i]);
                *(bool *)(config + 1 + i) = true;
            }
        }
    }

    void HandleWlanLclCmdsConfig(const char *cmd, const char *value, DLogConfig *config)
    {
        constexpr const char *service = "wlan:lcl";
        constexpr const char *cmds[] = {"disable_openmastermode", "disable_closemastermode", "disable_openclientmode", "disable_closeclientmode", "disable_openspectatormode", "disable_closespectatormode", "disable_getmacaddress", "disable_createbss", "disable_destroybss", "disable_startscan", "disable_stopscan", "disable_connect", "disable_cancelconnect", "disable_join", "disable_canceljoin", "disable_disconnect", "disable_setbeaconlostcount", "disable_getsystemevent", "disable_getconnectionstatus", "disable_getclientstatus", "disable_getbssindicationevent", "disable_getbssindicationinfo", "disable_getstate", "disable_getallowedchannels", "disable_addie", "disable_deleteie", "disable_putframeraw", "disable_cancelgetframe", "disable_createrxentry", "disable_deleterxentry", "disable_addethertypetorxentry", "disable_deleteethertypefromrxentry", "disable_addmatchingdatatorxentry", "disable_removematchingdatafromrxentry", "disable_getscanresult", "disable_putactionframeoneshot", "disable_setactionframewithbeacon", "disable_cancelactionframewithbeacon", "disable_createrxentryforactionframe", "disable_deleterxentryforactionframe", "disable_addsubtypetorxentryforactionframe", "disable_deletesubtypefromrxentryforactionframe", "disable_cancelgetactionframe", "disable_getrssi", "disable_setmaxassociationnumber", "disable_cmd45", "disable_cmd46", "disable_cmd47", "disable_cmd48", "disable_cmd49", "disable_cmd50", "disable_cmd51"};

        for (int i = 0; i < 52; i++)
        {
            if (strcasecmp(cmd, cmds[i]) == 0 && strcasecmp(value, "1") == 0)
            {
                LogDisabledCommand(service, cmds[i]);
                *(bool *)(config + 31 + i) = true;
            }
        }
    }

    int ParseIniHandler(void *user_ctx, const char *section, const char *name, const char *value)
    {
        auto config = reinterpret_cast<DLogConfig *>(user_ctx);

        if (strcasecmp(section, "ldn_u") == 0)
        {
            if (strcasecmp(name, "enable_mitm") == 0)
            {
                if (strcasecmp(value, "0") == 0)
                {
                    config->ldn_u.enable_mitm = false;
                    DEBUG_LOG("CONFIG> Disabled mitm for: 'ldn:u'");
                }
            }
        }
        else if (strcasecmp(section, "ldn_u.commands") == 0)
        {
            HandleLdnUCmdsConfig(name, value, config);
        }
        else if (strcasecmp(section, "wlan_lcl") == 0)
        {
            if (strcasecmp(name, "enable_mitm") == 0)
            {
                if (strcasecmp(value, "0") == 0)
                {
                    config->wlan_lcl.enable_mitm = false;
                    DEBUG_LOG("CONFIG> Disabled mitm for: 'wlan:lcl'");
                }
            }
        }
        else if (strcasecmp(section, "wlan_lcl.commands") == 0)
        {
            HandleWlanLclCmdsConfig(name, value, config);
        }
        else
        {
            return 0;
        }
        return 1;
    }

    Result ReadConfig()
    {
        fs::FileHandle file;
        bool has_file;
        R_TRY(fs::HasFile(&has_file, config_path));
        if (has_file)
        {
            R_TRY(fs::OpenFile(&file, config_path, fs::OpenMode_Read));
            int rc = util::ini::ParseFile(file, &g_config, ParseIniHandler);
            fs::CloseFile(file);
            if (rc < 0)
            {
                DEBUG_LOG("CONFIG> Couldn't load config. Code: %d", rc);
                R_RETURN(rc);
            }
        }
        else
        {
            DEBUG_LOG("CONFIG> No config file found. Skipping.");
        }

        R_SUCCEED();
    }

    DLogConfig *GetConfigInstance()
    {
        return &g_config;
    }
}
