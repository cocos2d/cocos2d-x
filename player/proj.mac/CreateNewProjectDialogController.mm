
#import "CreateNewProjectDialogController.h"
#include "SimulatorConfig.h"

@implementation CreateNewProjectDialogController

@synthesize textFieldProjetLocation;
@synthesize textFieldPackageName;
@synthesize textView;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
    NSLog(@"[CreateNewProjectDialogController dealloc]");
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (IBAction) onSelectProjectLocation:(id)sender
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:@"Select New Project Location"];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:YES];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];

    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSString *path = [[openDlg.URLs objectAtIndex:0] path];
        [textFieldProjetLocation setStringValue:path];
    }
}

- (IBAction) onCancel:(id)sender
{
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}

- (IBAction) onCreate:(id)sender
{
    // check all filed
    NSString *projectLocation = [textFieldProjetLocation stringValue];
    NSString *packageName = [textFieldPackageName stringValue];
//
    
    // run script
    NSString *createProjectShellFilePath = [NSString stringWithFormat:@"%s%@", SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath().c_str(),@"bin/create_project.sh"];
    NSString *commandLine = [NSString stringWithFormat:@"%@ -f -p %@ -o %@", createProjectShellFilePath, packageName, projectLocation];
    [[[textView textStorage] mutableString] appendString:commandLine];
    
    NSTask *task;
    task = [[NSTask alloc] init];
    [task setLaunchPath: createProjectShellFilePath];
    
    NSArray *arguments;
    arguments = [NSArray arrayWithObjects: @"-f",
                                            [NSString stringWithFormat:@"-p %@", packageName],
                                            [NSString stringWithFormat:@"-o %@", projectLocation], nil];
    [task setArguments: arguments];
    
    NSPipe *pipe;
    pipe = [NSPipe pipe];
    [task setStandardOutput: pipe];
    
    NSFileHandle *file;
    file = [pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data;
    data = [file readDataToEndOfFile];
    
    NSString *string;
    string = [[NSString alloc] initWithData: data encoding: NSUTF8StringEncoding];
    
    [[[textView textStorage] mutableString] appendString:string];
    
    [string release];
    [task release];
}

- (IBAction) onPackageNameChanged:(id)sender
{

}

@end
