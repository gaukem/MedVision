# MedVision.Viewer - Phase 1 Implementation Guide

## Phase 1 Overview
**Duration:** 2 weeks  
**Goal:** Build foundation for DICOM viewer with basic single-image display capabilities

## Objectives
By the end of Phase 1, you will have:
- ? MedVision.Imaging library with pixel data extraction
- ? MedVision.Rendering library with DirectX 11 setup
- ? MedVision.Viewer application that can:
  - Open and display a single DICOM file
  - Apply window/level adjustments with mouse
  - Pan and zoom the image
  - Display basic DICOM information

## Week 1: Image Processing Library

### Day 1-2: Create MedVision.Imaging Project

#### Step 1: Create Project Structure
```
MedVision.Imaging/
戍式式 include/medvision/imaging/
弛   戍式式 DicomImage.h
弛   戍式式 PixelDataProcessor.h
弛   戍式式 WindowLevel.h
弛   戌式式 ImageBuffer.h
戍式式 src/
弛   戍式式 DicomImage.cpp
弛   戍式式 PixelDataProcessor.cpp
弛   戍式式 WindowLevel.cpp
弛   戌式式 ImageBuffer.cpp
戍式式 MedVision.Imaging.vcxproj
戌式式 README.md
```

#### Step 2: Implement DicomImage Class
**File: `include/medvision/imaging/DicomImage.h`**

**Purpose:** High-level wrapper around DicomDataSet with image-specific operations

**Key Methods:**
```cpp
class DicomImage {
public:
    DicomImage(const medvision::dicom::DicomDataSet& dataset);
    
    // Image dimensions
    uint16_t GetWidth() const;
    uint16_t GetHeight() const;
    uint16_t GetBitsAllocated() const;
    uint16_t GetBitsStored() const;
    
    // Pixel data access
    bool HasPixelData() const;
    const uint8_t* GetRawPixelData() const;
    size_t GetPixelDataSize() const;
    
    // Image attributes
    std::string GetPhotometricInterpretation() const;
    uint16_t GetSamplesPerPixel() const;
    bool IsSigned() const;
    
    // Window/Level presets
    bool GetWindowCenter(double& center) const;
    bool GetWindowWidth(double& width) const;
    
    // Rescale parameters
    bool GetRescaleSlope(double& slope) const;
    bool GetRescaleIntercept(double& intercept) const;
    
    // Patient info (convenience)
    std::string GetPatientName() const;
    std::string GetStudyDescription() const;
    std::string GetModality() const;
};
```

#### Step 3: Implement PixelDataProcessor
**File: `include/medvision/imaging/PixelDataProcessor.h`**

**Purpose:** Extract and process raw pixel data into usable format

**Key Methods:**
```cpp
class PixelDataProcessor {
public:
    // Process raw DICOM pixel data to normalized float buffer
    static bool ProcessPixelData(
        const DicomImage& image,
        std::vector<float>& outputBuffer
    );
    
    // Apply rescale slope/intercept
    static void ApplyRescale(
        std::vector<float>& buffer,
        double slope,
        double intercept
    );
    
    // Apply modality LUT
    static void ApplyModalityLUT(
        std::vector<float>& buffer,
        const std::vector<uint16_t>& lut
    );
    
private:
    // Handle different bit depths
    static bool Process8Bit(const uint8_t* data, size_t pixels, std::vector<float>& output);
    static bool Process16Bit(const uint8_t* data, size_t pixels, bool isSigned, std::vector<float>& output);
};
```

**Implementation Notes:**
- Convert all pixel data to normalized float [0.0, 1.0] or actual values
- Handle both signed and unsigned data
- Apply rescale slope/intercept if present
- For 16-bit: `value = pixelValue * slope + intercept`

#### Step 4: Implement WindowLevel
**File: `include/medvision/imaging/WindowLevel.h`**

**Purpose:** Apply window/level transformations for display

**Key Methods:**
```cpp
class WindowLevel {
public:
    WindowLevel(double center, double width);
    
    void SetCenter(double center);
    void SetWidth(double width);
    double GetCenter() const;
    double GetWidth() const;
    
    // Apply W/L to pixel buffer (in-place or to new buffer)
    void Apply(const std::vector<float>& input, std::vector<uint8_t>& output) const;
    
    // Calculate W/L from percentiles (auto W/L)
    static WindowLevel FromPercentiles(const std::vector<float>& pixels, double lowPct, double highPct);
    
    // Common presets
    static WindowLevel Lung() { return WindowLevel(-600, 1500); }      // CT Lung
    static WindowLevel Abdomen() { return WindowLevel(40, 400); }      // CT Abdomen
    static WindowLevel Bone() { return WindowLevel(300, 1500); }       // CT Bone
    static WindowLevel Brain() { return WindowLevel(40, 80); }         // CT Brain
    
private:
    double center_;
    double width_;
};
```

**Window/Level Formula:**
```
if (pixelValue <= (center - width/2))    output = 0
else if (pixelValue >= (center + width/2)) output = 255
else output = ((pixelValue - (center - 0.5)) / (width - 1) + 0.5) * 255
```

### Day 3-4: Test MedVision.Imaging

#### Create Test Application
**File: `MedVision.Imaging/tests/test_imaging.cpp`**

```cpp
#include "medvision/dicom/DicomReader.h"
#include "medvision/imaging/DicomImage.h"
#include "medvision/imaging/PixelDataProcessor.h"
#include "medvision/imaging/WindowLevel.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: test_imaging <dicom_file>" << std::endl;
        return 1;
    }
    
    // Read DICOM file
    medvision::dicom::DicomReader reader;
    medvision::dicom::DicomDataSet dataset;
    if (!reader.ReadFile(argv[1], dataset)) {
        std::cerr << "Error: " << reader.GetLastError() << std::endl;
        return 1;
    }
    
    // Wrap in DicomImage
    medvision::imaging::DicomImage image(dataset);
    
    std::cout << "Image: " << image.GetWidth() << "x" << image.GetHeight() << std::endl;
    std::cout << "Bits: " << image.GetBitsAllocated() << std::endl;
    std::cout << "Modality: " << image.GetModality() << std::endl;
    
    // Process pixel data
    std::vector<float> pixelBuffer;
    if (!medvision::imaging::PixelDataProcessor::ProcessPixelData(image, pixelBuffer)) {
        std::cerr << "Failed to process pixel data" << std::endl;
        return 1;
    }
    
    std::cout << "Processed " << pixelBuffer.size() << " pixels" << std::endl;
    
    // Apply window/level
    double center, width;
    if (image.GetWindowCenter(center) && image.GetWindowWidth(width)) {
        std::cout << "W/L from DICOM: " << width << "/" << center << std::endl;
    } else {
        // Auto W/L
        auto wl = medvision::imaging::WindowLevel::FromPercentiles(pixelBuffer, 0.05, 0.95);
        center = wl.GetCenter();
        width = wl.GetWidth();
        std::cout << "Auto W/L: " << width << "/" << center << std::endl;
    }
    
    medvision::imaging::WindowLevel wl(center, width);
    std::vector<uint8_t> displayBuffer;
    wl.Apply(pixelBuffer, displayBuffer);
    
    std::cout << "Created display buffer: " << displayBuffer.size() << " bytes" << std::endl;
    
    // Could save to BMP here for visual verification
    
    return 0;
}
```

## Week 2: Rendering & Viewer Application

### Day 5-6: Create MedVision.Rendering Project

#### Step 1: Create Project Structure
```
MedVision.Rendering/
戍式式 include/medvision/rendering/
弛   戍式式 D3DContext.h           # DirectX 11 device/context
弛   戍式式 Texture2D.h            # Texture wrapper
弛   戍式式 Shader.h               # Shader compilation/management
弛   戌式式 ImageRenderer.h        # High-level 2D image renderer
戍式式 src/
弛   戍式式 D3DContext.cpp
弛   戍式式 Texture2D.cpp
弛   戍式式 Shader.cpp
弛   戍式式 ImageRenderer.cpp
弛   戌式式 shaders/
弛       戍式式 image_vs.hlsl      # Vertex shader
弛       戌式式 image_ps.hlsl      # Pixel shader
戌式式 MedVision.Rendering.vcxproj
```

#### Step 2: Implement D3DContext
**File: `include/medvision/rendering/D3DContext.h`**

**Purpose:** Manage DirectX 11 device and swap chain

```cpp
class D3DContext {
public:
    D3DContext();
    ~D3DContext();
    
    // Initialize D3D11 for a window
    bool Initialize(HWND hwnd, uint32_t width, uint32_t height);
    void Shutdown();
    
    // Accessors
    ID3D11Device* GetDevice() const { return device_; }
    ID3D11DeviceContext* GetContext() const { return context_; }
    IDXGISwapChain* GetSwapChain() const { return swapChain_; }
    ID3D11RenderTargetView* GetBackBufferRTV() const { return backBufferRTV_; }
    
    // Frame operations
    void BeginFrame(float clearColor[4]);
    void EndFrame();
    void Present();
    
    // Resize
    bool Resize(uint32_t width, uint32_t height);
    
private:
    ID3D11Device* device_;
    ID3D11DeviceContext* context_;
    IDXGISwapChain* swapChain_;
    ID3D11RenderTargetView* backBufferRTV_;
    
    uint32_t width_;
    uint32_t height_;
};
```

#### Step 3: Implement Texture2D
**File: `include/medvision/rendering/Texture2D.h`**

**Purpose:** GPU texture management

```cpp
class Texture2D {
public:
    Texture2D(D3DContext* context);
    ~Texture2D();
    
    // Create texture from pixel data
    bool Create(
        uint32_t width,
        uint32_t height,
        DXGI_FORMAT format,
        const void* data,
        uint32_t pitch
    );
    
    // Update texture data
    bool Update(const void* data, uint32_t pitch);
    
    // Accessors
    ID3D11Texture2D* GetTexture() const { return texture_; }
    ID3D11ShaderResourceView* GetSRV() const { return srv_; }
    uint32_t GetWidth() const { return width_; }
    uint32_t GetHeight() const { return height_; }
    
private:
    D3DContext* context_;
    ID3D11Texture2D* texture_;
    ID3D11ShaderResourceView* srv_;
    uint32_t width_;
    uint32_t height_;
};
```

#### Step 4: Implement ImageRenderer
**File: `include/medvision/rendering/ImageRenderer.h`**

**Purpose:** High-level API for rendering 2D images

```cpp
class ImageRenderer {
public:
    ImageRenderer(D3DContext* context);
    ~ImageRenderer();
    
    bool Initialize();
    
    // Render image to current render target
    void RenderImage(
        Texture2D* texture,
        float x, float y,              // Position (normalized -1 to 1)
        float width, float height,     // Size (normalized)
        float zoom = 1.0f
    );
    
private:
    D3DContext* context_;
    ID3D11VertexShader* vertexShader_;
    ID3D11PixelShader* pixelShader_;
    ID3D11Buffer* vertexBuffer_;
    ID3D11Buffer* constantBuffer_;
    ID3D11SamplerState* sampler_;
    ID3D11InputLayout* inputLayout_;
};
```

#### Step 5: Create Shaders
**File: `src/shaders/image_vs.hlsl`**

```hlsl
// Vertex Shader
struct VS_INPUT {
    float2 Position : POSITION;
    float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT {
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

cbuffer Constants : register(b0) {
    float2 offset;      // Pan offset
    float2 scale;       // Zoom scale
    float4 padding;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output;
    output.Position = float4(input.Position * scale + offset, 0.0f, 1.0f);
    output.TexCoord = input.TexCoord;
    return output;
}
```

**File: `src/shaders/image_ps.hlsl`**

```hlsl
// Pixel Shader
Texture2D imageTexture : register(t0);
SamplerState imageSampler : register(s0);

struct PS_INPUT {
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET {
    float gray = imageTexture.Sample(imageSampler, input.TexCoord).r;
    return float4(gray, gray, gray, 1.0f);
}
```

### Day 7-9: Create MedVision.Viewer Application

#### Step 1: Create Project Structure
```
MedVision.Viewer/
戍式式 src/
弛   戍式式 main.cpp               # WinMain entry point
弛   戍式式 Application.cpp/h      # Application singleton
弛   戍式式 MainWindow.cpp/h       # Main window class
弛   戌式式 ViewerPanel.cpp/h      # Image viewport
戍式式 resources/
弛   戍式式 app.ico                # Application icon
弛   戌式式 app.rc                 # Windows resources
戌式式 MedVision.Viewer.vcxproj
```

#### Step 2: Implement Main Window
**File: `src/main.cpp`**

```cpp
#include "MainWindow.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    medvision::viewer::MainWindow window;
    
    if (!window.Create(hInstance, 1280, 720, L"MedVision DICOM Viewer")) {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_ICONERROR);
        return -1;
    }
    
    window.Show(nCmdShow);
    
    return window.Run();
}
```

**File: `src/MainWindow.h`**

```cpp
#pragma once
#include "medvision/rendering/D3DContext.h"
#include "medvision/rendering/ImageRenderer.h"
#include "medvision/rendering/Texture2D.h"
#include "medvision/imaging/DicomImage.h"
#include "medvision/imaging/WindowLevel.h"
#include <Windows.h>
#include <string>
#include <memory>

namespace medvision {
namespace viewer {

class MainWindow {
public:
    MainWindow();
    ~MainWindow();
    
    bool Create(HINSTANCE hInstance, int width, int height, const wchar_t* title);
    void Show(int nCmdShow);
    int Run();
    
    // File operations
    void OpenFile();
    void CloseFile();
    
private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
    
    void OnResize(uint32_t width, uint32_t height);
    void OnPaint();
    void OnMouseMove(int x, int y);
    void OnMouseWheel(int delta);
    void OnLeftButtonDown(int x, int y);
    void OnLeftButtonUp(int x, int y);
    
    void UpdateWindowLevel(int dx, int dy);
    void UpdatePan(int dx, int dy);
    void UpdateZoom(float delta);
    void Render();
    
    void LoadDicomFile(const std::string& filePath);
    
private:
    HWND hwnd_;
    HINSTANCE hInstance_;
    
    // Rendering
    std::unique_ptr<medvision::rendering::D3DContext> d3dContext_;
    std::unique_ptr<medvision::rendering::ImageRenderer> imageRenderer_;
    std::unique_ptr<medvision::rendering::Texture2D> imageTexture_;
    
    // Image data
    std::unique_ptr<medvision::imaging::DicomImage> currentImage_;
    std::vector<float> pixelBuffer_;
    std::vector<uint8_t> displayBuffer_;
    medvision::imaging::WindowLevel windowLevel_;
    
    // Interaction state
    bool isWindowLeveling_;
    bool isPanning_;
    int lastMouseX_;
    int lastMouseY_;
    float panX_;
    float panY_;
    float zoom_;
};

} // namespace viewer
} // namespace medvision
```

#### Step 3: Implement Key Features

**Mouse Interaction Implementation:**

```cpp
void MainWindow::OnLeftButtonDown(int x, int y) {
    lastMouseX_ = x;
    lastMouseY_ = y;
    
    // Check modifiers
    if (GetKeyState(VK_CONTROL) & 0x8000) {
        isPanning_ = true;
    } else {
        isWindowLeveling_ = true;
    }
    
    SetCapture(hwnd_);
}

void MainWindow::OnMouseMove(int x, int y) {
    if (isWindowLeveling_) {
        int dx = x - lastMouseX_;
        int dy = y - lastMouseY_;
        UpdateWindowLevel(dx, dy);
    } else if (isPanning_) {
        int dx = x - lastMouseX_;
        int dy = y - lastMouseY_;
        UpdatePan(dx, dy);
    }
    
    lastMouseX_ = x;
    lastMouseY_ = y;
}

void MainWindow::UpdateWindowLevel(int dx, int dy) {
    // Horizontal = width, Vertical = center
    double newWidth = windowLevel_.GetWidth() + dx * 2.0;
    double newCenter = windowLevel_.GetCenter() - dy * 2.0;
    
    if (newWidth < 1.0) newWidth = 1.0;
    
    windowLevel_.SetWidth(newWidth);
    windowLevel_.SetCenter(newCenter);
    
    // Reapply W/L and update texture
    windowLevel_.Apply(pixelBuffer_, displayBuffer_);
    imageTexture_->Update(displayBuffer_.data(), currentImage_->GetWidth());
    
    // Redraw
    InvalidateRect(hwnd_, NULL, FALSE);
}
```

### Day 10: Testing & Documentation

#### Create User Testing Checklist
- [ ] Open various DICOM files (8-bit, 16-bit, signed, unsigned)
- [ ] Verify window/level adjustment with mouse
- [ ] Test pan with Ctrl+Drag
- [ ] Test zoom with mouse wheel
- [ ] Verify display of patient information
- [ ] Test with different modalities (CT, MR, CR, DX)

#### Performance Testing
- [ ] Load time for typical 512x512 image
- [ ] Rendering FPS (should be 60 FPS)
- [ ] Memory usage for single image
- [ ] Window/level responsiveness

#### Create README
**File: `MedVision.Viewer/README.md`**

```markdown
# MedVision.Viewer

Desktop DICOM image viewer application.

## Phase 1 Features
- Open single DICOM file
- Display grayscale images (8-bit, 16-bit)
- Window/Level adjustment with mouse drag
- Pan with Ctrl + drag
- Zoom with mouse wheel
- Display patient information

## Controls
- **Left Drag:** Adjust Window/Level
- **Ctrl + Left Drag:** Pan image
- **Mouse Wheel:** Zoom in/out
- **Ctrl + O:** Open file
- **Ctrl + W:** Close file

## Build Requirements
- Visual Studio 2022
- Windows SDK 10.0+
- DirectX 11
- C++14

## Dependencies
- MedVision.Dicom
- MedVision.Imaging
- MedVision.Rendering

## Building
```
msbuild MedVision.Viewer.vcxproj /p:Configuration=Release /p:Platform=x64
```

## Running
```
MedVision.Viewer.exe [optional_dicom_file.dcm]
```
```

## Phase 1 Deliverables Checklist

### Code Deliverables
- [ ] MedVision.Imaging project created
  - [ ] DicomImage class implemented
  - [ ] PixelDataProcessor implemented
  - [ ] WindowLevel implemented
  - [ ] Unit tests pass
  
- [ ] MedVision.Rendering project created
  - [ ] D3DContext implemented
  - [ ] Texture2D implemented
  - [ ] ImageRenderer implemented
  - [ ] Shaders compiled

- [ ] MedVision.Viewer application created
  - [ ] MainWindow implemented
  - [ ] File open dialog working
  - [ ] Image rendering working
  - [ ] Mouse interactions working
  - [ ] Application icon set

### Documentation Deliverables
- [ ] Architecture document created (`Docs/MedVision_Viewer_Architecture.md`)
- [ ] Solution structure updated (`Docs/Solution_Structure.md`)
- [ ] Phase 1 guide created (`Docs/Phase1_Implementation.md`)
- [ ] Each project has README.md
- [ ] Code comments added

### Testing Deliverables
- [ ] Test application for MedVision.Imaging
- [ ] Manual testing checklist completed
- [ ] Performance baseline recorded
- [ ] At least 5 different DICOM files tested

## Common Issues & Solutions

### Issue: Texture shows black screen
**Solution:** Check that display buffer is properly created and W/L is applied. Verify pixel data size matches texture dimensions.

### Issue: Mouse interaction laggy
**Solution:** Ensure texture update is efficient. Consider only updating on mouse release for large images, or use GPU-based W/L shader.

### Issue: Cannot open DICOM file
**Solution:** Verify MedVision.Dicom correctly reads the file first with example_usage. Check if pixel data element exists.

### Issue: Image appears too bright/dark
**Solution:** Check rescale slope/intercept. Use auto W/L from percentiles. Verify bits stored vs bits allocated.

## Next Steps: Phase 2 Preparation

After Phase 1 is complete, prepare for Phase 2:
1. Research ImGui integration with DirectX 11
2. Design Study/Series/Instance data model
3. Plan thumbnail generation strategy
4. Sketch UI layout for multi-panel interface

---
**Version:** 1.0  
**Last Updated:** 2024  
**Status:** IN PROGRESS
