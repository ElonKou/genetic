//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// File   :main.cpp
// Author :elonkou
// E-mail :elonkou@ktime.cc
// Date   :Mon 07 Jan 2019 05:33:32 PM CST
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include <iostream>
#include "core.hh"
#include "frame.hh"
#include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
using namespace std;

static void ShowExampleMenuFile();
static void ShowExampleAppMainMenuBar();

int main() {
    windowView view;
    // Controller con;
    // con.loop();
    // con.print();

    // string robbie_path =
    //     "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/0_487.txt";
    // Controller con = Controller();
    // con.train();
    // Robbie rob = con.loadRobbie(robbie_path);
    // Robbie rob;
    // rob.print();
    // Robbie rob = Robbie();
    // Map mp = Map();
    // mp.print(rob.start);
    // con.playScreen(rob, mp);

    // GLFWwindow* window = init_window();
    // load_font();
    // set_GL(window);
    // set_new_theme();

    // bool my_tool_active = true;
    // bool show_demo_window = true;
    // bool show_app_main_menu_bar = true;
    // bool show_overlay_bar = true;

    // Drawing
    while (!glfwWindowShouldClose(view.window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Draw window
        // ImGui::Begin("Tools", &my_tool_active, 0);
        // ImGui::Text("Hello from another window!");
        // ImGui::Text("Hello, world %d", 123);
        // if (ImGui::Button("Save")) {
        //     // do stuff
        //     cout << my_tool_active << endl;
        // }
        // ImGui::End();
        view.drawWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(view.window);
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

// int main() {
//     string robbie_path =
//         "/home/elonkou/ELONKOU/03.GENETIC/genetic/results/0_487.txt";
//     Controller con = Controller();
//     // con.train();
//     Robbie rob = con.loadRobbie(robbie_path);
//     // Robbie rob;
//     // rob.print();
//     // Robbie rob = Robbie();
//     Map mp = Map();
//     // mp.print(rob.start);
//     con.playScreen(rob, mp);
//     // rob.play(mp);
//     // mp.print(rob.pos);
//     return 0;
// }