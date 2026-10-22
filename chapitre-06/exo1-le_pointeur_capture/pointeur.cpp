#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

static void ConfigureAppData(NkAppData &data) {
  data.appName = "le_pointeur_capture";
}

NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
  (void)state;

  NkWindowConfig config;
  config.title = "Le pointeur capture";
  config.width = 1000;
  config.height = 720;
  config.centered = true;

  NkWindow window(config);
  if (!window.IsValid()) {
    return 1;
  }

  bool running = true;
  bool captured = true;
  window.ShowMouse(false);
  window.ClipMouseToClient(true);
  window.CaptureMouse(true);
  window.SetTitle("Le pointeur capture - capture et clip actifs (Espace)");

  NkEventSystem &events = NkEvents();
  events.AddEventCallback<NkWindowCloseEvent>(
      [&](NkWindowCloseEvent *) { running = false; });
  events.AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent *event) {
    if (event->GetKey() == NkKey::NK_ESCAPE) {
      running = false;
      return;
    }

    if (event->GetKey() == NkKey::NK_SPACE) {
      captured = !captured;
      window.ClipMouseToClient(captured);
      window.CaptureMouse(captured);
      window.ShowMouse(!captured);
      window.SetTitle(captured
                          ? "Le pointeur capture - capture et clip actifs (Espace)"
                          : "Le pointeur capture - capture relachee (Espace)");
    }
  });

  while (running && window.IsOpen()) {
    events.PollEvents();
  }

  window.ClipMouseToClient(false);
  window.CaptureMouse(false);
  window.ShowMouse(true);
  return 0;
}
