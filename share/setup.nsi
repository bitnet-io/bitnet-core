Name "Bitnet Core (64-bit)"

RequestExecutionLevel highest
SetCompressor /SOLID lzma
SetDateSave off
Unicode true

# Uncomment these lines when investigating reproducibility errors
#SetCompress off
#SetDatablockOptimize off

# General Symbol Definitions
!define REGKEY "SOFTWARE\$(^Name)"
!define COMPANY "Bitnet Core project"
!define URL https://bitnetcore.org/

# MUI Symbol Definitions
!define MUI_ICON "/home/c4pt/opt/bitnet-core/share/pixmaps/bitnet.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "/home/c4pt/opt/bitnet-core/share/pixmaps/nsis-wizard.bmp"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_HEADERIMAGE_BITMAP "/home/c4pt/opt/bitnet-core/share/pixmaps/nsis-header.bmp"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Bitnet Core"
!define MUI_FINISHPAGE_RUN "$WINDIR\explorer.exe"
!define MUI_FINISHPAGE_RUN_PARAMETERS $INSTDIR\bitnet-qt
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "/home/c4pt/opt/bitnet-core/share/pixmaps/nsis-wizard.bmp"
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI2.nsh
!include x64.nsh

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
InstallDir $PROGRAMFILES64\Bitnet
CRCCheck force
XPStyle on
BrandingText " "
ShowInstDetails show
VIProductVersion 24.99.0.0
VIAddVersionKey ProductName "Bitnet Core"
VIAddVersionKey ProductVersion "24.99.0"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "24.99.0"
VIAddVersionKey FileDescription "Installer for Bitnet Core"
VIAddVersionKey LegalCopyright "Copyright (C) 2009-2023 The Bitnet Core developers"
InstallDirRegKey HKCU "${REGKEY}" Path
ShowUninstDetails show

# Installer sections
Section -Main SEC0000
    SetOutPath $INSTDIR
    SetOverwrite on
    File /home/c4pt/opt/bitnet-core/release/bitnet-qt
    File /oname=COPYING.txt /home/c4pt/opt/bitnet-core/COPYING
    File /oname=readme.txt /home/c4pt/opt/bitnet-core/doc/README_windows.txt
    File /home/c4pt/opt/bitnet-core/share/examples/bitnet.conf
    SetOutPath $INSTDIR\share\rpcauth
    File /home/c4pt/opt/bitnet-core/share/rpcauth/*.*
    SetOutPath $INSTDIR\daemon
    File /home/c4pt/opt/bitnet-core/release/bitnetd
    File /home/c4pt/opt/bitnet-core/release/bitnet-cli
    File /home/c4pt/opt/bitnet-core/release/bitnet-tx
    File /home/c4pt/opt/bitnet-core/release/bitnet-wallet
    File /home/c4pt/opt/bitnet-core/release/test_bitnet
    SetOutPath $INSTDIR
    WriteRegStr HKCU "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0001
    WriteRegStr HKCU "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\$(^Name).lnk" $INSTDIR\bitnet-qt
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Bitnet Core (testnet, 64-bit).lnk" "$INSTDIR\bitnet-qt" "-testnet" "$INSTDIR\bitnet-qt" 1
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk" $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_END
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "24.99.0"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\bitnet-qt.exe
    WriteRegStr HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1
    WriteRegStr HKCR "bitnet" "URL Protocol" ""
    WriteRegStr HKCR "bitnet" "" "URL:Bitnet"
    WriteRegStr HKCR "bitnet\DefaultIcon" "" $INSTDIR\bitnet-qt
    WriteRegStr HKCR "bitnet\shell\open\command" "" '"$INSTDIR\bitnet-qt" "%1"'
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKCU "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000
    Delete /REBOOTOK $INSTDIR\bitnet-qt
    Delete /REBOOTOK $INSTDIR\COPYING.txt
    Delete /REBOOTOK $INSTDIR\readme.txt
    Delete /REBOOTOK $INSTDIR\bitnet.conf
    RMDir /r /REBOOTOK $INSTDIR\share
    RMDir /r /REBOOTOK $INSTDIR\daemon
    DeleteRegValue HKCU "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall $(^Name).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\$(^Name).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Bitnet Core (testnet, 64-bit).lnk"
    Delete /REBOOTOK "$SMSTARTUP\Bitnet.lnk"
    Delete /REBOOTOK $INSTDIR\uninstall.exe
    Delete /REBOOTOK $INSTDIR\debug.log
    Delete /REBOOTOK $INSTDIR\db.log
    DeleteRegValue HKCU "${REGKEY}" StartMenuGroup
    DeleteRegValue HKCU "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKCU "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKCU "${REGKEY}"
    DeleteRegKey HKCR "bitnet"
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

# Installer functions
Function .onInit
    InitPluginsDir
    ${If} ${RunningX64}
      ; disable registry redirection (enable access to 64-bit portion of registry)
      SetRegView 64
    ${Else}
      MessageBox MB_OK|MB_ICONSTOP "Cannot install 64-bit version on a 32-bit system."
      Abort
    ${EndIf}
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKCU "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd
