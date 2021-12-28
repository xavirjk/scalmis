; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "scalmis"
#define MyAppVersion "1.0"
#define MyAppPublisher "j_k, Inc."
#define MyAppExeName "SCALMIS.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".exe"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{D17CCD15-08D3-41CC-BCC7-0B4F062485AA}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\{#MyAppName}
ChangesAssociations=yes
DisableProgramGroupPage=yes
LicenseFile=E:\updatesBar\scalmis\LICENSE.txt
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=E:\qt-rec\SCALMIS\installer
OutputBaseFilename=setup
SetupIconFile=E:\qt-rec\SCALMIS\SCALMIS\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "E:\updatesBar\scalmis\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\_RELEASE"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6OpenGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6Qml.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6QmlModels.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6QmlWorkerScript.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6Quick.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6QuickControls2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6QuickControls2Impl.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\Qt6QuickTemplates2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\s_update.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\s_updateLib.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\SCALMIS.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\SCALMIS-LIB.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\updatesBar\scalmis\imgs\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\updatesBar\scalmis\quick\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\updatesBar\scalmis\win\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
