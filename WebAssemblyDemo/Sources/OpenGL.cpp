#include "OpenGL.hpp"

EMSCRIPTEN_KEEPALIVE
OpenGL::OpenGL() {

  _vertices[0].setPosition(-0.6f, -0.4f);
  _vertices[0].setColor(255, 0, 0, 1);

  _vertices[1].setPosition(0.6f, -0.4f);
  _vertices[1].setColor(0, 255, 0, 1);

  _vertices[2].setPosition(0.f, 0.6f);
  _vertices[2].setColor(0, 0, 255, 1);
  OpenGL::_vertexShaderText =
    "#version 300 es\n"
      "uniform mat4 MVP;\n"
      "in lowp vec3 vCol;\n"
      "in lowp vec2 vPos;\n"
      "out lowp vec3 i_color;\n"
      "void main()\n"
      "{\n"
      "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
      "    i_color = vCol;\n"
      "}\n";
  OpenGL::_fragmentShaderText =
    "#version 300 es\n"
      "in lowp vec3 i_color;\n"
      "out lowp vec4 o_color;\n"
      "void main()\n"
      "{\n"
      "    o_color = vec4(i_color, 1.0);\n"
      "}\n";

  if (!glfwInit()) {
    fputs("Failed to initialize GLFW", stderr);
    emscripten_force_exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  _window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

  if (!_window) {
    fputs("Failed to create GLFW window", stderr);
    glfwTerminate();
    emscripten_force_exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(_window);

  glGenBuffers(1, &_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

  _vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(_vertexShader, 1, &_vertexShaderText, NULL);
  glCompileShader(_vertexShader);
  checkCompiled(_vertexShader);

  _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(_fragmentShader, 1, &_fragmentShaderText, NULL);
  glCompileShader(_fragmentShader);
  checkCompiled(_fragmentShader);

  _program = glCreateProgram();
  glAttachShader(_program, _vertexShader);
  glAttachShader(_program, _fragmentShader);
  glLinkProgram(_program);
  checkLinked(_program);

  _mvpLocation = glGetUniformLocation(_program, "MVP");
  _vposLocation = glGetAttribLocation(_program, "vPos");
  _vcolLocation = glGetAttribLocation(_program, "vCol");
  glEnableVertexAttribArray(_vposLocation);
  glVertexAttribPointer(_vposLocation, 2, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 5, (void*) 0);
  glEnableVertexAttribArray(_vcolLocation);
  glVertexAttribPointer(_vcolLocation, 3, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 5, (void*) (sizeof(float) * 2));


  emscripten_set_main_loop(generateFrame, 0, 0);
}

OpenGL::~OpenGL() {

}

EMSCRIPTEN_KEEPALIVE
void OpenGL::outputError(int error, const char* msg) {
  fprintf(stderr, "Error: %s\n", msg);
}

EMSCRIPTEN_KEEPALIVE
void OpenGL::generateFrame() {
  float ratio;
  int width, height;
  mat4x4 m, p, mvp;
  glfwGetFramebufferSize(_window, &width, &height);
  ratio = width / (float) height;
  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);
  mat4x4_identity(m);
  mat4x4_rotate_Z(m, m, (float) glfwGetTime());
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);
  glUseProgram(_program);
  glUniformMatrix4fv(_mvpLocation, 1, GL_FALSE, (const GLfloat*) mvp);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glfwSwapBuffers(_window);
  glfwPollEvents();
}

EMSCRIPTEN_KEEPALIVE
int OpenGL::checkCompiled(GLuint shader) {
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    GLint maxLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);

    GLchar err_log[maxLen];
    glGetShaderInfoLog(shader, maxLen, &maxLen, &err_log[0]);
    glDeleteShader(shader);

    fprintf(stderr, "Shader compilation failed: %s\n", err_log);
  }

  return success;
}

EMSCRIPTEN_KEEPALIVE
int OpenGL::checkLinked(GLuint program) {
  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (success == GL_FALSE) {
    GLint maxLen = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);

    GLchar err_log[maxLen];
    glGetProgramInfoLog(program, maxLen, &maxLen, &err_log[0]);

    fprintf(stderr, "Program linking failed: %s\n", err_log);
  }

  return success;
}
