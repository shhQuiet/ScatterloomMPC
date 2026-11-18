import AppKit
import Foundation
let folder=CommandLine.arguments[1]
for (id,title) in [("center","CENTER"),("left-right","LEFT TO RIGHT"),("right-left","RIGHT TO LEFT"),("spread","SPREAD")] {
 for active in [false,true] {
  let im=NSImage(size:NSSize(width:180,height:56));im.lockFocus()
  let path=NSBezierPath(roundedRect:NSRect(x:2,y:2,width:176,height:52),xRadius:7,yRadius:7)
  (active ? NSColor(calibratedRed:0.72,green:0.38,blue:0.06,alpha:1) : NSColor(calibratedRed:0.12,green:0.11,blue:0.10,alpha:1)).setFill();path.fill()
  NSColor(calibratedRed:0.95,green:0.61,blue:0.22,alpha:1).setStroke();path.lineWidth=2;path.stroke()
  let attrs:[NSAttributedString.Key:Any]=[.font:NSFont.systemFont(ofSize:19,weight:.bold),.foregroundColor:NSColor(calibratedRed:1,green:0.82,blue:0.55,alpha:1)]
  let size=(title as NSString).size(withAttributes:attrs);(title as NSString).draw(at:NSPoint(x:(180-size.width)/2,y:(56-size.height)/2),withAttributes:attrs)
  im.unlockFocus();let rep=NSBitmapImageRep(data:im.tiffRepresentation!)!;let pathOut=folder+"/stereo-"+id+(active ? "-on.png":"-off.png")
  try! rep.representation(using:.png,properties:[:])!.write(to:URL(fileURLWithPath:pathOut))
  let t=Process();t.executableURL=URL(fileURLWithPath:"/usr/bin/sips");t.arguments=["-z","56","180",pathOut];t.standardOutput=FileHandle.nullDevice;try! t.run();t.waitUntilExit()
 }
}
