package Ruby;

import org.lwjgl.Version;
import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.opengl.GL;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.NULL;

public class Window {
    private int width, height;
    private String title;
    private long glfwWindow;

    private static Window window = null;

    private Window() {
        this.height = 1080;
        this.width = 1920;
        this.title = "test_engine";
    }

    public static Window get(){
        if (Window.window == null) {
            Window.window = new Window();
        }
    return Window.window;
    }

    public void run(){
        System.out.println("Hello LWJGL "+ Version.getVersion() + "!");

        init();
        loop();
    }

    public void init(){
        //error callback
        GLFWErrorCallback.createPrint(System.err).set();

        //init
        if (!glfwInit()) {
            throw new IllegalStateException("can't initialisze GLFW.");
        }

        //config GLFW
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

        //creating window
        glfwWindow = glfwCreateWindow(this.width, this.height, this.title, NULL, NULL);
        if (glfwWindow == NULL) throw new IllegalStateException("Failed to create the GLFW window");

        //Make OpenGL context current
        glfwMakeContextCurrent(glfwWindow);

        //enableVSync
        glfwSwapInterval(1);

        //make window visible
        glfwShowWindow(glfwWindow);

        GL.createCapabilities();
    }

    public void loop(){
        while (!glfwWindowShouldClose(glfwWindow)){
            //Poll events
            glfwPollEvents();

            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(glfwWindow);
        }
    }
}
