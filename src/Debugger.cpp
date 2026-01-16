#include "Debugger.hpp"
#include "Chip8.hpp"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <sstream>
#include <iomanip>

#include "../cmake-build-debug/_deps/imgui-src/imgui.h"
#include "../cmake-build-debug/_deps/imgui-src/backends/imgui_impl_sdl3.h"
#include "../cmake-build-debug/_deps/imgui-src/backends/imgui_impl_sdlrenderer3.h"

Debugger::Debugger() = default;

Debugger::~Debugger() {
    shutdown();
}

bool Debugger::init() {
    window = SDL_CreateWindow(
        "MC8E debugger",
        600, 400,
        SDL_WINDOW_RESIZABLE);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_DestroyWindow(window);
        window = nullptr;
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    return true;
}

void Debugger::shutdown() {
    if (ImGui::GetCurrentContext() != nullptr) {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Debugger::processEvent(SDL_Event& event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

std::string Debugger::disassemble(uint16_t opcode) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << opcode;
    return ss.str();
}

void Debugger::renderControlWindow() {
    ImGui::SetNextWindowPos(ImVec2(5,305), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiCond_FirstUseEver);

    ImGui::Begin("Controls");

    if (ImGui::Button(paused ? "Resume" : "Pause", ImVec2(100, 25))) {
        paused = !paused;
    }

    ImGui::SameLine();

    ImGui::BeginDisabled(!paused);
    if (ImGui::Button("Step", ImVec2(70, 25))) stepRequested = true;
    ImGui::EndDisabled();

    ImGui::Text(paused ? "Paused" : "Running");
    ImGui::Text("Space: Pause | N: Next step");

    ImGui::End();
}

void Debugger::renderInstructionWindow(const Chip8 &chip8) {
    ImGui::SetNextWindowPos(ImVec2(5,5), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200,300), ImGuiCond_FirstUseEver);

    ImGui::Begin("Instructions: Following PC");

    const auto& memory = chip8.getMemory();
    uint16_t pc = chip8.getPC();

    int startAddr = std::max(0x200, (int)pc - 10);//start at memory
    int endAddr = std::min(4094, startAddr + 30);

    for (int addr = startAddr; addr < endAddr; addr+= 2) {
        uint16_t opcode = (memory[addr] << 8) | memory[addr + 1];

        bool isCurr = (addr == pc);
        if (isCurr) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));

        ImGui::Text("Instruction %03X: %s", addr,  disassemble(opcode).c_str());

        if (isCurr) {
            ImGui::PopStyleColor();
            ImGui::SetScrollHereY(0.8f);
        }
    }
    ImGui::End();
}

void Debugger::renderRegistersWindow(const Chip8& chip8) {
    ImGui::SetNextWindowPos(ImVec2(210,5), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300,100), ImGuiCond_FirstUseEver);

    ImGui::Begin("CPU Registers", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    const auto& V = chip8.getV();
    if (ImGui::BeginTable("VRegs", 4, ImGuiTableFlags_BordersV)) {
        for (int i = 0; i < 16; ++i) {
            ImGui::TableNextColumn();
            ImGui::Text("V%X: %02X", i, V[i]);
        }
        ImGui::EndTable();
    }
    ImGui::Separator();

    ImGui::Text("PC: %03X", chip8.getPC());
    ImGui::SameLine();
    ImGui::Text("I: %03X", chip8.getI());
    ImGui::SameLine();
    ImGui::Text("SP: %02X", chip8.getSP());

    ImGui::Text("DT: %02X", chip8.getDelayTimer());
    ImGui::SameLine();
    ImGui::Text("ST: %02X", chip8.getSoundTimer());

    ImGui::End();
}

void Debugger:: renderStackWindow(const Chip8& chip8) {
    ImGui::SetNextWindowPos(ImVec2(210,150), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(220,200), ImGuiCond_FirstUseEver);

    ImGui::Begin("Stack");

    const auto& stack = chip8.getStack();
    uint8_t sp = chip8.getSP();

    for (int i = 0; i < 16; i++) {
        if (i < sp) {
            ImGui::Text("Depth [%X] %0X3", i, stack[i]);
        } else {
            ImGui::TextDisabled("Depth [%X] ---", i);
        }
    }

    ImGui::End();
}

void Debugger::render(Chip8& chip8) {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (ImGui::IsKeyPressed(ImGuiKey_Space)) paused = !paused;
    if (paused && ImGui::IsKeyPressed(ImGuiKey_N)) stepRequested = true;

    renderInstructionWindow(chip8);
    renderRegistersWindow(chip8);
    renderStackWindow(chip8);
    renderControlWindow();

    ImGui::Render();
    SDL_SetRenderDrawColor(renderer, 45, 45, 45, 255);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}

