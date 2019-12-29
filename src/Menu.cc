/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : core/Menu.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年11月11日 星期一 22时51分36秒
================================================================*/

#include "Menu.hh"
#include "DynamicClass.hh"

DYN_DECLARE(Menu);

Menu::Menu() {}

Menu::~Menu() {}

void Menu::showMenuFile() {
    if (ImGui::MenuItem("New")) {
    }
    if (ImGui::MenuItem("Open", "Ctrl+O")) {
    }
    if (ImGui::BeginMenu("Open Recent")) {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More..")) {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
    }
    if (ImGui::MenuItem("Save As..")) {
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Preferences")) {
        static bool enabled = true;
        ImGui::MenuItem("auto save", "", &enabled);
        ImGui::MenuItem("Author");
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Colors")) {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(
                p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Quit", "Alt+F4")) {
    }
}

void Menu::show() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            showMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem("Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }
    }

    if (ImGui::BeginMenu("View")) {
        static bool tab_menu_button;
        static bool tab_close_button;
        if (ImGui::MenuItem("Control")) {
            show_control_window = !show_control_window;
        }
        if (ImGui::MenuItem("Display")) {
            show_simplemap_window = !show_simplemap_window;
        }
        if (ImGui::MenuItem("Overview")) {
            show_overlay_bar = !show_overlay_bar;
        }
        if (ImGui::MenuItem("Node view")) {
            show_node_window = !show_node_window;
        }
        if (ImGui::MenuItem("Inspector")) {
            show_inspector_window = !show_inspector_window;
        }
        if (ImGui::MenuItem("Graph")) {
            show_graph_window = !show_graph_window;
        }
        if (ImGui::MenuItem("Editor")) {
            show_editor_window = !show_editor_window;
        }
        if (ImGui::MenuItem("Demo")) {
            show_demo_window = !show_demo_window;
        }
        ImGui::Separator();

        if (ImGui::MenuItem("Tab menu", NULL, &tab_menu_button)) {
            dockspace_flag ^= ImGuiDockNodeFlags_NoWindowMenuButton;
        }
        if (ImGui::MenuItem("Close button", NULL, &tab_close_button)) {
            dockspace_flag ^= ImGuiDockNodeFlags_NoCloseButton;
        }

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Theme")) {
        if (ImGui::MenuItem("Dark theme")) {
        }
        if (ImGui::MenuItem("Light theme")) {
        }
        if (ImGui::MenuItem("Github theme")) {
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("help")) {
        if (ImGui::MenuItem("Simple")) {
        }
        ImGui::SameLine();
        showHelpMarker("This is a simple text for help.");
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}