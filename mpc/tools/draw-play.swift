import AppKit
for (state,on) in [("on",true),("off",false)] {
 let image=NSImage(size:NSSize(width:91,height:70)); image.lockFocus()
 let path=NSBezierPath(roundedRect:NSRect(x:1,y:1,width:89,height:68),xRadius:8,yRadius:8)
 NSColor(calibratedWhite:0.11,alpha:0.9).setFill(); path.fill()
 NSColor(calibratedWhite:0.40,alpha:1).setStroke(); path.lineWidth=2; path.stroke()
 NSColor(calibratedWhite:0.78,alpha:1).setFill()
 if on { NSBezierPath(roundedRect:NSRect(x:31,y:20,width:9,height:30),xRadius:1,yRadius:1).fill(); NSBezierPath(roundedRect:NSRect(x:51,y:20,width:9,height:30),xRadius:1,yRadius:1).fill() }
 else { let t=NSBezierPath(); t.move(to:NSPoint(x:34,y:19)); t.line(to:NSPoint(x:62,y:35)); t.line(to:NSPoint(x:34,y:51)); t.close(); t.fill() }
 image.unlockFocus()
 let bitmap = NSBitmapImageRep(bitmapDataPlanes: nil, pixelsWide: 91, pixelsHigh: 70,
   bitsPerSample: 8, samplesPerPixel: 4, hasAlpha: true, isPlanar: false,
   colorSpaceName: .deviceRGB, bytesPerRow: 0, bitsPerPixel: 0)!
 NSGraphicsContext.saveGraphicsState()
 NSGraphicsContext.current = NSGraphicsContext(bitmapImageRep: bitmap)
 NSGraphicsContext.current?.imageInterpolation = .high
 image.draw(in: NSRect(x: 0, y: 0, width: 91, height: 70),
            from: NSRect(x: 0, y: 0, width: 91, height: 70), operation: .copy, fraction: 1.0)
 NSGraphicsContext.restoreGraphicsState()
 try bitmap.representation(using:.png,properties:[:])!.write(to:URL(fileURLWithPath:CommandLine.arguments[1]+"/play-control-"+state+".png"))
}
