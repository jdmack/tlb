#include <string>
#include <list>

#include "gfx/Shader.h"
#include "util/Logger.h"
#include "util/FileReader.h"

Shader::Shader()
{
    programID_ = 0;
    initSuccess = false;
}

Shader::Shader(const char* vertexFilename, const char* fragmentFilename) : Shader()
{
    if(!init()) {
        return;
    }
    if(!attachShader(vertexFilename, GL_VERTEX_SHADER)) {
        return;
    }
    if(!attachShader(fragmentFilename, GL_FRAGMENT_SHADER)) {
        return;
    }
    if(!finalize()) {
        return;
    }
    initSuccess = true;
}

Shader::~Shader()
{
    // Delete the intermediate shader objects that have been added to the program
    for(std::list<GLuint>::iterator it = shaderList_.begin(); it != shaderList_.end(); it++) {
        glDeleteShader(*it);
    }

    if(programID_ != 0) {
        glDeleteProgram(programID_);
        programID_ = 0;
    }
}

bool Shader::init()
{
    // Check if shortcut constructor was used
    if(initSuccess) {
        return true;
    }
    // Generate program
    programID_ = glCreateProgram();

    if(programID_ == 0) {
        Logger::write(Logger::ss << "ERROR: unable to create shader program");
        return false;
    }

    initSuccess = true;
    return true;
}

bool Shader::attachShader(const char* filename, GLenum shaderType)
{
    // Load shader source
    std::string shaderStr;

    if(!FileReader::readFile(filename, shaderStr)) {
        Logger::write(Logger::ss << "ERROR: unable to load shader source from file: " << filename);
        return false;
    }

    const GLchar * shaderSrc = shaderStr.c_str();
    
    // Create shader
    GLuint shaderObj = glCreateShader(shaderType);

    if(shaderObj == 0) {
        Logger::write(Logger::ss << "ERROR: unable to create shader object of type: " << shaderType);
        return false;
    }

    // Save the shader object - will be deleted in the destructor
    shaderList_.push_back(shaderObj);

    // Set shader source
    glShaderSource(shaderObj, 1, &shaderSrc, NULL);

    // Compile shader
    glCompileShader(shaderObj);

    // Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &shaderCompiled);

    if(shaderCompiled != GL_TRUE) {
        Logger::write(Logger::ss << "ERROR: Could not compile shader " << shaderObj << " of type " << shaderType);
        printShaderLog(shaderObj);
        return false;
    }

    // Attach shader to program
    glAttachShader(programID_, shaderObj);

    return true;
}


bool Shader::finalize()
{
    // Link program
    glLinkProgram(programID_);

    // Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programID_, GL_LINK_STATUS, &programSuccess);

    if(programSuccess != GL_TRUE) {
        Logger::write(Logger::ss << "ERROR: Could not link program: " << programID_);
        printProgramLog(programID_); 
        return false;
    }

    // Validate program
    glValidateProgram(programID_);
    glGetProgramiv(programID_, GL_VALIDATE_STATUS, &programSuccess);
    if(programSuccess != GL_TRUE) {
        Logger::write(Logger::ss << "ERROR: Invalid shader program: " << programID_);
        printProgramLog(programID_); 
        return false;
    }

    // Delete the intermediate shader objects that have been added to the program
    for(std::list<GLuint>::iterator it = shaderList_.begin(); it != shaderList_.end(); it++) {
        glDeleteShader(*it);
    }

    shaderList_.clear();

    return true;
}

void Shader::enable()
{
    glUseProgram(programID_);
}

void Shader::disable()
{
    glUseProgram(0);
}

GLint Shader::getAttribLocation(const char* attribName)
{
    GLuint location = glGetAttribLocation(programID_, attribName);

    if(location == -1) {
        Logger::write(Logger::ss << "ERROR: Unable to get attribute location of " << attribName);
    }

    return location;
}

GLint Shader::getUniformLocation(const char* uniformName)
{
    GLuint location = glGetUniformLocation(programID_, uniformName);

    if(location == -1) {
        Logger::write(Logger::ss << "ERROR: Unable to get uniform location of " << uniformName);
    }

    return location;
}

GLint Shader::getProgramParam(GLint param)
{
    GLint ret;
    glGetProgramiv(programID_, param, &ret);
    return ret;
}

void Shader::printProgramLog(GLuint program)
{
    // Make sure name is program
    if(glIsProgram(program)) {
        
        // Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        // Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // Allocate string
        char * infoLog = new char[maxLength];

        // Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);

        if(infoLogLength > 0) {
            // Print log
            printf("%s\n", infoLog);
        }
        
        // Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a program\n", program);
    }
}

void Shader::printShaderLog(GLuint shader)
{
    // Make sure name is shader
    if(glIsShader(shader)) {
        
        // Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        // Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // Allocate string
        char * infoLog = new char[maxLength];

        // Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

        if(infoLogLength > 0) {
            // Print log
            printf("%s\n", infoLog);
        }
        
        // Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a shader\n", shader);
    }
}

