# MedVision.Viewer - Project Setup Checklist

This checklist guides you through creating the new projects for the viewer application.

## Prerequisites Verification

- [ ] Visual Studio 2022 installed
- [ ] Windows SDK 10.0+ installed
- [ ] MedVision.Dicom project builds successfully
- [ ] MedVision.Dicom.Tests runs successfully
- [ ] Git repository set up at `https://github.com/gaukem/MedVision`

## Phase 1 - Project Creation

### Step 1: Create MedVision.Imaging Project

#### 1.1 Create Static Library Project
- [ ] Open Visual Studio 2022
- [ ] File ¡æ New ¡æ Project
- [ ] Select "Static Library (C++)"
- [ ] **Name:** `MedVision.Imaging`
- [ ] **Location:** `G:\Daryls Workspace\MedVision\`
- [ ] **Solution:** Add to existing solution
- [ ] Click "Create"

#### 1.2 Configure Project Properties
- [ ] Right-click project ¡æ Properties
- [ ] **Configuration:** All Configurations
- [ ] **Platform:** x64

**General:**
- [ ] Configuration Type: Static Library (.lib)
- [ ] C++ Language Standard: ISO C++14 Standard (/std:c++14)
- [ ] Windows SDK Version: 10.0 (latest installed)

**C/C++ ¡æ General:**
- [ ] Additional Include Directories: 
  ```
  $(SolutionDir)MedVision.Dicom\include;
  $(ProjectDir)include;
  %(AdditionalIncludeDirectories)
  ```

**C/C++ ¡æ Preprocessor:**
- [ ] Debug: `_DEBUG;%(PreprocessorDefinitions)`
- [ ] Release: `NDEBUG;%(PreprocessorDefinitions)`

**Librarian ¡æ General:**
- [ ] Output Directory:
  - Debug: `$(SolutionDir)bin\$(Platform)\$(Configuration)\`
  - Release: `$(SolutionDir)bin\$(Platform)\$(Configuration)\`
- [ ] Intermediate Directory: `$(SolutionDir)obj\$(ProjectName)\$(Platform)\$(Configuration)\`

#### 1.3 Create Folder Structure
Create these folders in `MedVision.Imaging/`:
- [ ] `include/medvision/imaging/`
- [ ] `src/`
- [ ] `tests/`

#### 1.4 Add Project Reference
- [ ] Right-click MedVision.Imaging ¡æ Add ¡æ Reference
- [ ] Check `MedVision.Dicom`
- [ ] Click OK

---

### Step 2: Create MedVision.Rendering Project

#### 2.1 Create Static Library Project
- [ ] File ¡æ New ¡æ Project
- [ ] Select "Static Library (C++)"
- [ ] **Name:** `MedVision.Rendering`
- [ ] **Location:** `G:\Daryls Workspace\MedVision\`
- [ ] **Solution:** Add to existing solution

#### 2.2 Configure Project Properties
- [ ] Configuration: All Configurations, Platform: x64

**General:**
- [ ] Configuration Type: Static Library (.lib)
- [ ] C++ Language Standard: ISO C++14 Standard (/std:c++14)

**C/C++ ¡æ General:**
- [ ] Additional Include Directories:
  ```
  $(ProjectDir)include;
  %(AdditionalIncludeDirectories)
  ```

**Linker ¡æ Input ¡æ Additional Dependencies:**
- [ ] Add: `d3d11.lib;dxgi.lib;d3dcompiler.lib;%(AdditionalDependencies)`

**Librarian ¡æ General:**
- [ ] Output Directory: `$(SolutionDir)bin\$(Platform)\$(Configuration)\`
- [ ] Intermediate Directory: `$(SolutionDir)obj\$(ProjectName)\$(Platform)\$(Configuration)\`

#### 2.3 Create Folder Structure
- [ ] `include/medvision/rendering/`
- [ ] `src/`
- [ ] `src/shaders/`

---

### Step 3: Create MedVision.Database Project (Optional for Phase 1)

Skip for Phase 1, create in Phase 3.

---

### Step 4: Create MedVision.Viewer Application

#### 4.1 Create Windows Desktop Application
- [ ] File ¡æ New ¡æ Project
- [ ] Select "Windows Desktop Application" or "Empty Project"
- [ ] **Name:** `MedVision.Viewer`
- [ ] **Location:** `G:\Daryls Workspace\MedVision\`
- [ ] **Solution:** Add to existing solution

#### 4.2 Configure Project Properties
- [ ] Configuration: All Configurations, Platform: x64

**General:**
- [ ] Configuration Type: Application (.exe)
- [ ] C++ Language Standard: ISO C++14 Standard (/std:c++14)
- [ ] Windows SDK Version: 10.0 (latest)
- [ ] Character Set: Use Unicode Character Set

**C/C++ ¡æ General:**
- [ ] Additional Include Directories:
  ```
  $(SolutionDir)MedVision.Dicom\include;
  $(SolutionDir)MedVision.Imaging\include;
  $(SolutionDir)MedVision.Rendering\include;
  $(ProjectDir)src;
  %(AdditionalIncludeDirectories)
  ```

**C/C++ ¡æ Preprocessor:**
- [ ] Debug: `_DEBUG;_WINDOWS;%(PreprocessorDefinitions)`
- [ ] Release: `NDEBUG;_WINDOWS;%(PreprocessorDefinitions)`

**Linker ¡æ System:**
- [ ] SubSystem: Windows (/SUBSYSTEM:WINDOWS)

**Linker ¡æ Input ¡æ Additional Dependencies:**
- [ ] Add: `d3d11.lib;dxgi.lib;d3dcompiler.lib;%(AdditionalDependencies)`

**Linker ¡æ General:**
- [ ] Output Directory: `$(SolutionDir)bin\$(Platform)\$(Configuration)\`
- [ ] Intermediate Directory: `$(SolutionDir)obj\$(ProjectName)\$(Platform)\$(Configuration)\`

**Linker ¡æ Advanced:**
- [ ] Entry Point: `wWinMainCRTStartup` (for Unicode)

#### 4.3 Create Folder Structure
- [ ] `src/`
- [ ] `src/UI/`
- [ ] `src/Controllers/`
- [ ] `src/Models/`
- [ ] `src/Tools/`
- [ ] `resources/`
- [ ] `resources/icons/`
- [ ] `resources/shaders/`

#### 4.4 Add Project References
- [ ] Right-click MedVision.Viewer ¡æ Add ¡æ Reference
- [ ] Check:
  - [ ] `MedVision.Dicom`
  - [ ] `MedVision.Imaging`
  - [ ] `MedVision.Rendering`

---

## Step 5: Verify Build Configuration

#### 5.1 Set Build Order
- [ ] Right-click solution ¡æ Project Dependencies
- [ ] Verify dependencies are correct:
  ```
  MedVision.Imaging depends on: MedVision.Dicom
  MedVision.Rendering depends on: (none)
  MedVision.Viewer depends on: All above
  ```

#### 5.2 Set Startup Project
- [ ] Right-click `MedVision.Viewer` ¡æ Set as Startup Project

#### 5.3 Test Build
- [ ] Build ¡æ Rebuild Solution
- [ ] Configuration: Debug, Platform: x64
- [ ] Verify all projects build successfully
- [ ] Check output directory: `bin\x64\Debug\`

---

## Step 6: Create Initial Files

### MedVision.Imaging

#### 6.1 Create Header Files
Create these files with class declarations (see Phase1_Implementation.md for details):

- [ ] `include/medvision/imaging/DicomImage.h`
- [ ] `include/medvision/imaging/PixelDataProcessor.h`
- [ ] `include/medvision/imaging/WindowLevel.h`
- [ ] `include/medvision/imaging/ImageBuffer.h`

#### 6.2 Create Source Files
- [ ] `src/DicomImage.cpp`
- [ ] `src/PixelDataProcessor.cpp`
- [ ] `src/WindowLevel.cpp`
- [ ] `src/ImageBuffer.cpp`

#### 6.3 Add Files to Project
- [ ] Right-click Header Files ¡æ Add ¡æ Existing Item ¡æ Select headers
- [ ] Right-click Source Files ¡æ Add ¡æ Existing Item ¡æ Select sources

#### 6.4 Create README
- [ ] Create `MedVision.Imaging/README.md`
- [ ] Document library purpose and API

---

### MedVision.Rendering

#### 6.5 Create Header Files
- [ ] `include/medvision/rendering/D3DContext.h`
- [ ] `include/medvision/rendering/Texture2D.h`
- [ ] `include/medvision/rendering/Shader.h`
- [ ] `include/medvision/rendering/ImageRenderer.h`

#### 6.6 Create Source Files
- [ ] `src/D3DContext.cpp`
- [ ] `src/Texture2D.cpp`
- [ ] `src/Shader.cpp`
- [ ] `src/ImageRenderer.cpp`

#### 6.7 Create Shader Files
- [ ] `src/shaders/image_vs.hlsl` (Vertex Shader)
- [ ] `src/shaders/image_ps.hlsl` (Pixel Shader)

#### 6.8 Configure Shader Compilation
For each .hlsl file:
- [ ] Right-click ¡æ Properties
- [ ] Item Type: HLSL Compiler
- [ ] Shader Type: Vertex Shader (vs_5_0) or Pixel Shader (ps_5_0)
- [ ] Shader Model: 5.0
- [ ] Output Files: `$(OutDir)%(Filename).cso`

#### 6.9 Add Files to Project
- [ ] Add all headers and sources to project
- [ ] Verify shaders compile during build

#### 6.10 Create README
- [ ] Create `MedVision.Rendering/README.md`

---

### MedVision.Viewer

#### 6.11 Create Source Files
- [ ] `src/main.cpp` (WinMain entry point)
- [ ] `src/Application.h`
- [ ] `src/Application.cpp`
- [ ] `src/MainWindow.h`
- [ ] `src/MainWindow.cpp`

#### 6.12 Create Resource Files
- [ ] Create `resources/app.rc` (Windows resource script)
- [ ] Create or add `resources/app.ico` (application icon)

#### 6.13 Configure Resources
- [ ] Right-click project ¡æ Add ¡æ Resource
- [ ] Add Icon resource
- [ ] Set IDI_APP_ICON

#### 6.14 Create README
- [ ] Create `MedVision.Viewer/README.md`

---

## Step 7: Implement Minimal Viable Code

### 7.1 MedVision.Imaging Stubs
Create minimal implementations that compile:

```cpp
// DicomImage.h - minimal declaration
class DicomImage {
public:
    DicomImage(const medvision::dicom::DicomDataSet& dataset);
    uint16_t GetWidth() const { return 512; }
    uint16_t GetHeight() const { return 512; }
};

// DicomImage.cpp - minimal implementation
DicomImage::DicomImage(const medvision::dicom::DicomDataSet& dataset) {
    // TODO: Extract dimensions
}
```

- [ ] Implement minimal DicomImage
- [ ] Implement minimal PixelDataProcessor
- [ ] Implement minimal WindowLevel
- [ ] Build and verify no errors

### 7.2 MedVision.Rendering Stubs
- [ ] Implement minimal D3DContext (device creation only)
- [ ] Implement minimal Texture2D (create but don't load)
- [ ] Implement minimal ImageRenderer (empty render function)
- [ ] Create basic shaders (passthrough)
- [ ] Build and verify no errors

### 7.3 MedVision.Viewer Minimal Application
- [ ] Implement WinMain that creates window
- [ ] Implement MainWindow with basic message loop
- [ ] Initialize D3D11 context
- [ ] Clear screen to blue color
- [ ] Build and run - verify blue window appears

---

## Step 8: Version Control

### 8.1 Update .gitignore
Add these patterns if not present:
```gitignore
# Build outputs
bin/
obj/
*.user
*.suo

# Visual Studio
.vs/
*.vcxproj.user
*.suo

# Compiled shaders
*.cso
```

### 8.2 Commit Project Structure
```bash
git add MedVision.Imaging/
git add MedVision.Rendering/
git add MedVision.Viewer/
git add Docs/
git commit -m "[Setup] Add MedVision.Viewer project structure

- Created MedVision.Imaging library project
- Created MedVision.Rendering library project  
- Created MedVision.Viewer application project
- Added comprehensive documentation
- Set up build configuration"
git push origin main
```

---

## Step 9: Documentation Updates

### 9.1 Update Solution README
- [ ] Edit `Docs/README.md`
- [ ] Add viewer project to overview
- [ ] Update technology stack

### 9.2 Create Per-Project READMEs
- [ ] `MedVision.Imaging/README.md` - Library API documentation
- [ ] `MedVision.Rendering/README.md` - Rendering API documentation
- [ ] `MedVision.Viewer/README.md` - Application usage guide

### 9.3 Update CI/CD Pipeline
- [ ] Edit `.github/workflows/ci.yml`
- [ ] Add build steps for new projects:
```yaml
- name: Build MedVision.Imaging
  shell: cmd
  run: msbuild "MedVision.Imaging\MedVision.Imaging.vcxproj" /p:Configuration=Debug /p:Platform=x64 /m

- name: Build MedVision.Rendering
  shell: cmd
  run: msbuild "MedVision.Rendering\MedVision.Rendering.vcxproj" /p:Configuration=Debug /p:Platform=x64 /m

- name: Build MedVision.Viewer
  shell: cmd
  run: msbuild "MedVision.Viewer\MedVision.Viewer.vcxproj" /p:Configuration=Debug /p:Platform=x64 /m
```

---

## Step 10: Validation

### 10.1 Build Verification
- [ ] Clean solution
- [ ] Rebuild All (Debug x64)
- [ ] Verify no errors
- [ ] Check bin/x64/Debug/ contains:
  - [ ] MedVision.Dicom.lib
  - [ ] MedVision.Imaging.lib
  - [ ] MedVision.Rendering.lib
  - [ ] MedVision.Viewer.exe

### 10.2 Run Verification
- [ ] Run MedVision.Viewer.exe
- [ ] Verify window appears (blue screen is OK for initial setup)
- [ ] Close window cleanly
- [ ] No crashes or errors

### 10.3 Git Status Check
- [ ] Run `git status`
- [ ] Ensure all new files are tracked
- [ ] Ensure build artifacts are ignored
- [ ] Commit any remaining changes

---

## Next Steps After Setup

Once all checkboxes above are complete:

1. **Start Phase 1 Week 1 Implementation**
   - Follow `Docs/Phase1_Implementation.md`
   - Implement DicomImage class fully
   - Implement PixelDataProcessor
   - Implement WindowLevel

2. **Create Test Application**
   - Build test_imaging.cpp
   - Test with real DICOM files

3. **Continue to Week 2**
   - Implement rendering components
   - Build functional viewer application

---

## Troubleshooting

### Issue: Project won't build
- Verify C++14 is selected in project properties
- Check all include directories are correct
- Ensure Windows SDK is installed

### Issue: Can't find d3d11.lib
- Install Windows SDK 10.0+
- Verify SDK is selected in project properties
- Check linker additional dependencies

### Issue: Shaders don't compile
- Verify HLSL files have correct item type
- Check shader model is set to 5.0
- Ensure output directory is writable

### Issue: Viewer.exe won't start
- Check all .lib files are built
- Verify project references are set
- Ensure subsystem is Windows, not Console

---

## Resources

- **Phase 1 Guide:** `Docs/Phase1_Implementation.md`
- **Architecture:** `Docs/MedVision_Viewer_Architecture.md`
- **Quick Reference:** `Docs/Quick_Reference.md`

---

**Setup Version:** 1.0  
**Last Updated:** 2024  
**Estimated Time:** 2-3 hours for complete setup
