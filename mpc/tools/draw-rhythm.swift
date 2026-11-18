import AppKit
import Foundation
let dir=CommandLine.arguments[1]
func save(_ image:NSImage,_ name:String) {
 let rep=NSBitmapImageRep(data:image.tiffRepresentation!)!
 let path=dir+"/"+name
 try! rep.representation(using:.png,properties:[:])!.write(to:URL(fileURLWithPath:path))
 // AppKit may rasterize at Retina scale; MPC film strips require exact pixels.
 let task=Process(); task.executableURL=URL(fileURLWithPath:"/usr/bin/sips")
 task.arguments=["-z",String(Int(image.size.height)),String(Int(image.size.width)),path]
 task.standardOutput=FileHandle.nullDevice; try! task.run(); task.waitUntilExit()
 precondition(task.terminationStatus == 0)

}
let play=NSImage(size:NSSize(width:24,height:48));play.lockFocus()
let outline=NSBezierPath(ovalIn:NSRect(x:1,y:1,width:22,height:22));outline.lineWidth=2.5
NSColor(calibratedRed:0.65,green:1,blue:1,alpha:1).setStroke();outline.stroke()
play.unlockFocus();save(play,"playhead-strip.png")
let base=NSImage(size:NSSize(width:240,height:240));base.lockFocus()
let circle=NSBezierPath(ovalIn:NSRect(x:10,y:10,width:220,height:220));circle.lineWidth=1.5
NSColor(calibratedRed:0.45,green:0.42,blue:0.36,alpha:0.65).setStroke();circle.stroke()
base.unlockFocus();save(base,"rhythm-ring.png")
let count=64
for i in 0..<count {
 let theta = -Double.pi/2 + 2*Double.pi*Double(i)/Double(count)
 let half=Double.pi/Double(count)*1.30
 let image=NSImage(size:NSSize(width:64,height:1536));image.lockFocus()
 for frame in 0..<24 {
  let fy=Double((23-frame)*64)
  func point(_ radius:Double,_ angle:Double)->NSPoint {
   NSPoint(x:32 + radius*cos(angle)-75*cos(theta), y:fy+32-radius*sin(angle)+75*sin(theta))
  }
  func shape(_ r0:Double,_ r1:Double) -> NSBezierPath {
   let p=NSBezierPath();p.move(to:point(r0,theta-half))
   for j in 0...5 {p.line(to:point(r1,theta-half+2*half*Double(j)/5))}
   for j in (0...5).reversed() {p.line(to:point(r0,theta-half+2*half*Double(j)/5))}
   p.close();return p
  }
  let grainLevel=frame % 6
  if grainLevel > 0 {
   let strength = Double(grainLevel - 1) / 4.0
   NSColor(calibratedRed:0.13+0.28*strength,green:0.30+0.43*strength,blue:0.28+0.40*strength,alpha:1).setFill()
   shape(50,104).fill()
   // Fine radial threads follow the ring; clip them to each segment.
   NSGraphicsContext.saveGraphicsState()
   shape(50,104).addClip()
   NSColor(calibratedRed:0.72,green:0.85,blue:0.71,alpha:0.10).setStroke()
   for r in stride(from: 52.0, through: 102.0, by: 5.0) {
    let thread=NSBezierPath(); thread.lineWidth=0.7
    thread.move(to:point(r,theta-half)); thread.line(to:point(r,theta+half)); thread.stroke()
   }
   NSGraphicsContext.restoreGraphicsState()
  }
  let ribbon=frame / 6
  if ribbon > 0 {
   let width=Double(ribbon)*2.55
   NSColor(calibratedRed:0.68,green:0.82,blue:0.61,alpha:0.8).setFill();shape(76-width/2,76+width/2).fill()
  }
 }
 image.unlockFocus();save(image,String(format:"rhythm-sector-%02d.png",i))
}
