
#import <Cocoa/Cocoa.h>
#import "ProjectConfig/SimulatorConfig.h"

@interface ProjectConfigDialogController : NSWindowController
{
    ProjectConfig projectConfig;

    NSTextField *textFieldProjectDirectory;
    NSTextField *textFieldScriptFile;
    NSTextField *textFieldWritablePath;
    NSPopUpButtonCell *popupScreenSize;
    NSTextField *textFieldScreenSizeWidth;
    NSTextField *textFieldScreenSizeHeight;
    NSMatrix *matrixScreenOrientation;
    NSButtonCell *buttonScreenOrientationPortait;
    NSButtonCell *buttonScreenOrientationLandscape;
    NSButton *buttonShowDebugConsole;
    NSButton *buttonWriteDebugLogToFile;
    NSButton *buttonLoadPrecompiledFramework;
    NSButton *buttonOpenProject;
}

@property (nonatomic, assign) ProjectConfig projectConfig;

@property (nonatomic, assign) IBOutlet NSTextField *textFieldProjectDirectory;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldScriptFile;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldWritablePath;
@property (nonatomic, assign) IBOutlet NSPopUpButtonCell *popupScreenSize;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldScreenSizeWidth;
@property (nonatomic, assign) IBOutlet NSTextField *textFieldScreenSizeHeight;
@property (nonatomic, assign) IBOutlet NSMatrix *matrixScreenOrientation;
@property (nonatomic, assign) IBOutlet NSButtonCell *buttonScreenOrientationPortait;
@property (nonatomic, assign) IBOutlet NSButtonCell *buttonScreenOrientationLandscape;
@property (nonatomic, assign) IBOutlet NSButton *buttonShowDebugConsole;
@property (nonatomic, assign) IBOutlet NSButton *buttonWriteDebugLogToFile;
@property (nonatomic, assign) IBOutlet NSButton *buttonLoadPrecompiledFramework;
@property (nonatomic, assign) IBOutlet NSButton *buttonOpenProject;

- (IBAction) browseProjectDirectory:(id)sender;
- (IBAction) browseScriptFile:(id)sender;
- (IBAction) browseWritablePath:(id)sender;

- (IBAction) onScreenSizeChanged:(id)sender;
- (IBAction) onScreenSizeTextFieldsChanged:(id)sender;
- (IBAction) onScreenOrientationChanged:(id)sender;
- (IBAction) onShowDebugConsoleChanged:(id)sender;
- (IBAction) onWriteDebugLogToFileChanged:(id)sender;
- (IBAction) onLoadPrecompiledFrameworkChanged:(id)sender;

- (IBAction) onCancel:(id)sender;
- (IBAction) onOpenProject:(id)sender;

@end
