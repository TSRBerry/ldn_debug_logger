#include "logging.hpp"
#include "dlog_config.hpp"

namespace ams::mitm
{
    namespace
    {
        constexpr const char *config_path = "sdmc:/config/ldn_debug_logger/dlog.ini";
        DLogConfig g_config = {.ldn_u = {.enable_mitm = true}, .wlan_lcl = {.enable_mitm = true}, .wlan_lg = {.enable_mitm = true}, .wlan_lga = {.enable_mitm = true}};
    }

    void LogDisabledCommand(const char *service, const char *cmd)
    {
        DEBUG_LOG("CONFIG> [%s] Disabled cmd: '%s'", service, cmd);
    }

    void HandleLdnUCmdsConfig(const char *cmd, const char *value, DLogConfig *config)
    {
        constexpr const char *service = "ldn:u";
        constexpr const char *cmds[] = {"disable_getstate", "disable_getnetworkinfo", "disable_getipv4address", "disable_getdisconnectreason", "disable_getsecurityparameter", "disable_getnetworkconfig", "disable_attachstatechangeevent", "disable_getnetworkinfolatestupdate", "disable_scan", "disable_scanprivate", "disable_setwirelesscontrollerrestriction", "disable_setbluetoothaudiodeviceconnectablemode", "disable_openaccesspoint", "disable_closeaccesspoint", "disable_createnetwork", "disable_createnetworkprivate", "disable_destroynetwork", "disable_reject", "disable_setadvertisedata", "disable_setstationacceptpolicy", "disable_addacceptfilterentry", "disable_clearacceptfilter", "disable_openstation", "disable_closestation", "disable_connect", "disable_connectprivate", "disable_disconnect", "disable_initialize", "disable_finalize", "disable_initialize2"};
        static_assert(sizeof(config->ldn_u.commands) == sizeof(cmds) / sizeof(char *));

        for (int i = 0; i < (int)(sizeof(cmds) / sizeof(char *)); i++)
        {
            if (strcasecmp(cmd, cmds[i]) == 0 && strcasecmp(value, "1") == 0)
            {
                LogDisabledCommand(service, cmds[i]);
                *((bool *)(&config->ldn_u.commands) + i) = true;
            }
        }
    }

    void HandleWlanLclCmdsConfig(const char *cmd, const char *value, DLogConfig *config)
    {
        constexpr const char *service = "wlan:lcl";
        constexpr const char *cmds[] = {"disable_openmode", "disable_closemode", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd41", "disable_cmd44foractionframe", "disable_cmd41foractionframe", "disable_cmd44", "disable_cmd41", "disable_cmd42", "disable_cmd43", "disable_cmd44", "disable_cmd45", "disable_cmd46", "disable_cmd47", "disable_cmd48", "disable_cmd49", "disable_cmd50", "disable_cmd51"};
        static_assert(sizeof(config->wlan_lcl.commands) == sizeof(cmds) / sizeof(char *));

        for (int i = 0; i < (int)(sizeof(cmds) / sizeof(char *)); i++)
        {
            if (strcasecmp(cmd, cmds[i]) == 0 && strcasecmp(value, "1") == 0)
            {
                LogDisabledCommand(service, cmds[i]);
                *((bool *)(&config->wlan_lcl.commands) + i) = true;
            }
        }
    }

    void HandleWlanLgCmdsConfig(const char *cmd, const char *value, DLogConfig *config)
    {
        constexpr const char *service = "wlan:lg";
        constexpr const char *cmds[] = {"disable_getframeraw"};
        static_assert(sizeof(config->wlan_lg.commands) == sizeof(cmds) / sizeof(char *));

        for (int i = 0; i < (int)(sizeof(cmds) / sizeof(char *)); i++)
        {
            if (strcasecmp(cmd, cmds[i]) == 0 && strcasecmp(value, "1") == 0)
            {
                LogDisabledCommand(service, cmds[i]);
                *((bool *)(&config->wlan_lcl.commands) + i) = true;
            }
        }
    }

    void HandleWlanLgaCmdsConfig(const char *cmd, const char *value, DLogConfig *config)
    {
        constexpr const char *service = "wlan:lga";
        constexpr const char *cmds[] = {"disable_getactionframe"};
        static_assert(sizeof(config->wlan_lga.commands) == sizeof(cmds) / sizeof(char *));

        for (int i = 0; i < (int)(sizeof(cmds) / sizeof(char *)); i++)
        {
            if (strcasecmp(cmd, cmds[i]) == 0 && strcasecmp(value, "1") == 0)
            {
                LogDisabledCommand(service, cmds[i]);
                *((bool *)(&config->wlan_lcl.commands) + i) = true;
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
        else if (strcasecmp(section, "wlan_lg") == 0)
        {
            if (strcasecmp(name, "enable_mitm") == 0)
            {
                if (strcasecmp(value, "0") == 0)
                {
                    config->wlan_lg.enable_mitm = false;
                    DEBUG_LOG("CONFIG> Disabled mitm for: 'wlan:lg'");
                }
            }
        }
        else if (strcasecmp(section, "wlan_lg.commands") == 0)
        {
            HandleWlanLgCmdsConfig(name, value, config);
        }
        else if (strcasecmp(section, "wlan_lga") == 0)
        {
            if (strcasecmp(name, "enable_mitm") == 0)
            {
                if (strcasecmp(value, "0") == 0)
                {
                    config->wlan_lga.enable_mitm = false;
                    DEBUG_LOG("CONFIG> Disabled mitm for: 'wlan:lga'");
                }
            }
        }
        else if (strcasecmp(section, "wlan_lga.commands") == 0)
        {
            HandleWlanLgaCmdsConfig(name, value, config);
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
