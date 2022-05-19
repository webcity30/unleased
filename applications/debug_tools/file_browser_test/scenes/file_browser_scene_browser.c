#include "../file_browser_app_i.h"
#include "furi/check.h"
#include "furi/log.h"
#include "furi_hal.h"
#include "m-string.h"

#define DEFAULT_PATH "/"
#define EXTENSION "*"

bool file_browser_scene_browser_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    FileBrowserApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_next_scene(app->scene_manager, FileBrowserSceneResult);
        consumed = true;
    } else if(event.type == SceneManagerEventTypeTick) {
    }
    return consumed;
}

static void file_browser_callback(void* context, bool state) {
    FileBrowserApp* app = context;
    furi_assert(app);
    view_dispatcher_send_custom_event(app->view_dispatcher, SceneManagerEventTypeCustom);

    UNUSED(state);
}

void file_browser_scene_browser_on_enter(void* context) {
    FileBrowserApp* app = context;

    file_browser_set_callback(app->file_browser, file_browser_callback, app);

    file_browser_start(app->file_browser, app->file_path);

    view_dispatcher_switch_to_view(app->view_dispatcher, FileBrowserAppViewBrowser);
}

void file_browser_scene_browser_on_exit(void* context) {
    FileBrowserApp* app = context;

    file_browser_stop(app->file_browser);
}
