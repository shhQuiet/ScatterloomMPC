import AppKit
let image = NSImage(size: NSSize(width: 1280, height: 624))
image.lockFocus()
let lines: [(String, CGFloat, CGFloat, Bool)] = [
("Thanks for using Scatterloom!",30,34,true),
("These are some basic explanations of the plugin, but some things will be left to discovery or mystery.",80,22,false),
("CAPTURE",140,25,true),
("Scatterloom has a 9-slot pool of samples. It analyzes the input and based on loudness level, captures",180,21,false),
("a short sample called a grain and places it into the grain pool. The automatic sensitivity works pretty",210,21,false),
("well, but you can turn it off and adjust manually. Capture is enabled, so it is always listening, or can be",240,21,false),
("disabled and the grains that are currently in the pool remain there.",270,21,false),
("PATTERN",335,25,true),
("Scatterloom generates a euclidean pattern to determine when to play grains using the steps and pulses",375,21,false),
("controls. Pulses is a division of steps, so 7/16 would be 7 pulses spread across 16 steps.",405,21,false),
("GRAIN SELECTION",450,25,true),
("As Scatterloom plays and the step counter advances,",485,21,false)]
for (text,y,size,bold) in lines {
 let font = bold ? NSFont.boldSystemFont(ofSize:size) : NSFont.systemFont(ofSize:size)
 let color = bold ? NSColor(calibratedRed:1,green:0.69,blue:0.23,alpha:1) : NSColor(calibratedRed:0.94,green:0.90,blue:0.84,alpha:1)
 (text as NSString).draw(at:NSPoint(x:45,y:624-y-size),withAttributes:[.font:font,.foregroundColor:color])
}
image.unlockFocus()
let bitmap=NSBitmapImageRep(data:image.tiffRepresentation!)!
try bitmap.representation(using:.png,properties:[:])!.write(to:URL(fileURLWithPath:CommandLine.arguments[1]))
