#include <iostream>

//Dear ImGui

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

//project
#include <Interface/interface.hpp>
#include <Mesh/mesh.hpp>
#include <Render/camera.hpp>
//OpenGL
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>

using namespace MSc;

// GLFW callbacks
void glfw_callback_error(int error, const char* description);

void glfw_callback_framebuffer_size(GLFWwindow* window, int width, int height);

void glfw_callback_key_press(GLFWwindow*, int, int, int, int);

void glfw_callback_cursor_pos(GLFWwindow* window, double xPos, double yPos);

void glfw_callback_mouse_button(GLFWwindow* window, int, int, int);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera = Camera(glm::vec3(-0.5f, 0.02f, -2.3f), glm::radians(0.f), glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool enableMouse = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(int argc, const char * argv[])
	{
        glfwSetErrorCallback(glfw_callback_error);
        if(!glfwInit())
	        return EXIT_FAILURE;

	    // OpenGL+GLSL versions
		const char* glsl_version = "#version 330";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  

	    GLFWwindow* window = glfwCreateWindow(1280, 720, "MSc Project", NULL, NULL);
		if (window == NULL)
			return EXIT_FAILURE;
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync

        //glfw call back function
        glfwSetFramebufferSizeCallback(window, &glfw_callback_framebuffer_size);
        //Set the input Mode
        glfwSetInputMode(window, GLFW_CURSOR, NULL);

        // Configure the GLFW window
        glfwSetKeyCallback(window, &glfw_callback_key_press);

        glfwSetMouseButtonCallback(window, &glfw_callback_mouse_button);

        glfwSetCursorPosCallback(window, &glfw_callback_cursor_pos);
    
    
	    //Setup Dear ImGui
	    // Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

	    //enable docking
	    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	    // Setup Dear ImGui style
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
		style.Colors[ImGuiCol_Button]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_Header]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_Separator]             = style.Colors[ImGuiCol_Border];
		style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
		style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_Tab]                   = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
		style.Colors[ImGuiCol_TabHovered]            = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
		style.Colors[ImGuiCol_TabActive]             = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused]          = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_DockingPreview]        = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
		style.Colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		style.Colors[ImGuiCol_DragDropTarget]        = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.5f);
		style.WindowRounding    = 10.0f;
		style.ChildRounding     = 5.0f;
		style.FrameRounding     = 5.0f;
		style.GrabRounding      = 10.0f;
		style.PopupRounding     = 10.0f;
		style.ScrollbarRounding = 10.0f;
		style.TabRounding       = 10.0f;

	        // Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init(glsl_version);

		//setup the constructors
        // glew imports all OpenGL extension methods
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
    
        //initilze constructors
        
#ifdef __APPLE__
        Shader shader("../../Shader/shader.vert", "../../Shader/shader.frag");
        Mesh mesh("../../assets/test.obj");
        mesh.ExportObj("../../assets/test1.obj");
        mesh.Initialize();
#else
        Shader shader("./Shader/shader.vert", "./Shader/shader.frag");
		Mesh mesh("./assets/test.obj");
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
        
#endif
        CellSet grid;
        Inspector inspector(&grid);
        Interface interface(&inspector);
        
	        // Main loop
			while (!glfwWindowShouldClose(window))
			{
				glfwPollEvents();

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				interface.ShowGUI();
				ImGui::ShowDemoWindow();

				ImGui::Render();

                
                // per-frame time logic
                // --------------------
                float currentFrame = static_cast<float>(glfwGetTime());
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                
				int window_w, window_h;
				glfwGetFramebufferSize(window, &window_w, &window_h);
				glViewport(0, 0, window_w, window_h);
				ImVec4 clear_colour = ImVec4(0.45f, 0.55f, 0.6f, 1.f);
				glClearColor(clear_colour.x * clear_colour.w, clear_colour.y * clear_colour.w, clear_colour.z * clear_colour.w, clear_colour.w);
				glClear(GL_COLOR_BUFFER_BIT);

                // render the triangle
                shader.use();

                // set up the MVP matrices.
                glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 projection = glm::perspective(glm::radians(60.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
                glm::mat4 view = camera.getViewMatrix();
                shader.setMat4("projection", projection);
                shader.setMat4("view", view);
                shader.setMat4("model", model);
                // render the loaded model
                
                mesh.Render(shader);
                
                //camera movement
                camera.updateCameraPosition(deltaTime);
                
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                
				glfwSwapBuffers(window);
                glfwPollEvents();
	        }

        //cleanup ImGui
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	    // Cleanup glfw
		glfwDestroyWindow(window);
		glfwTerminate();

		return EXIT_SUCCESS;

	}

void glfw_callback_framebuffer_size(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void glfw_callback_key_press(GLFWwindow* aWindow, int aKey, int /*aScanCode*/, int aAction, int /*aModifierFlags*/)
    {
        if(GLFW_KEY_L == aKey && GLFW_PRESS == aAction)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else if(GLFW_KEY_F == aKey && GLFW_PRESS ==aAction)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        
        if (GLFW_KEY_ESCAPE == aKey && GLFW_PRESS == aAction)
        {
            glfwSetWindowShouldClose(aWindow, GLFW_TRUE);
        }

        // forward/backward
        if (glfwGetKey(aWindow, GLFW_KEY_W) == GLFW_PRESS)
            camera.speedZ = 1.0f;
        else if (glfwGetKey(aWindow, GLFW_KEY_S) == GLFW_PRESS)
            camera.speedZ = -1.0f;
        else
        {
            camera.speedZ = 0.f;
        }

        // left/right
        if (glfwGetKey(aWindow, GLFW_KEY_A) == GLFW_PRESS)
            camera.speedX = -1.f;
        else if (glfwGetKey(aWindow, GLFW_KEY_D) == GLFW_PRESS)
            camera.speedX = 1.f;
        else
        {
            camera.speedX = 0.f;
        }

        // up/down
        if (glfwGetKey(aWindow, GLFW_KEY_Q) == GLFW_PRESS)
            camera.speedY = 1.f;
        else if (glfwGetKey(aWindow, GLFW_KEY_E) == GLFW_PRESS)
            camera.speedY = -1.f;
        else
        {
            camera.speedY = 0.f;
        }

        // speed up/down
        if (glfwGetKey(aWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.speedScalar = 10.f;
        else if (glfwGetKey(aWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.speedScalar = 0.05f;
        
       // std::cout <<glm::to_string(camera.position) << std::endl;
    }

    void glfw_callback_cursor_pos(GLFWwindow* window, double xPos, double yPos)
    {

        if (enableMouse == true)
        {
            if (firstMouse)
            {
                lastX = (float)xPos;
                lastY = (float)yPos;
                firstMouse = false;
            }

            float deltaX, deltaY;
            deltaX = (float)xPos - lastX;
            deltaY = lastY - (float)yPos;

            lastX = (float)xPos;
            lastY = (float)yPos;

            camera.processMouseMovement(deltaX, deltaY, deltaTime);
        }
    }

    void glfw_callback_mouse_button(GLFWwindow* window, int aButton, int aAction, int)
    {
        if (GLFW_MOUSE_BUTTON_RIGHT == aButton && GLFW_PRESS == aAction)
        {
            enableMouse = !enableMouse;
        }
    }

void glfw_callback_error(int error, const char* description)
{
    std::cout << "Glfw Error " << error << ": " << description << std::endl;
}

