import AppKit
import CoreGraphics
import ImageIO
import UniformTypeIdentifiers
let w = 1280, h = 628
let ctx = CGContext(data: nil, width: w, height: h, bitsPerComponent: 8, bytesPerRow: w * 4, space: CGColorSpaceCreateDeviceRGB(), bitmapInfo: CGImageAlphaInfo.premultipliedLast.rawValue)!
func color(_ r: CGFloat,_ g: CGFloat,_ b: CGFloat,_ a: CGFloat = 1) -> CGColor { CGColor(red:r,green:g,blue:b,alpha:a) }
// Draw the selected Euclidean artwork at the MPC page dimensions.
let backgroundURL = URL(fileURLWithPath: CommandLine.arguments[3]) as CFURL
let backgroundSource = CGImageSourceCreateWithURL(backgroundURL, nil)!
let background = CGImageSourceCreateImageAtIndex(backgroundSource, 0, nil)!
ctx.interpolationQuality = .high
ctx.draw(background, in: CGRect(x: 0, y: 0, width: w, height: h))
// A translucent light plate keeps the dark Elsewave lettering legible.
let logoPlate = CGPath(roundedRect: CGRect(x: 34, y: 26, width: 258, height: 100), cornerWidth: 9, cornerHeight: 9, transform: nil)
ctx.addPath(logoPlate); ctx.setFillColor(color(0.72, 0.75, 0.73, 0.18)); ctx.fillPath()
let nsctx=NSGraphicsContext(cgContext:ctx,flipped:false)
NSGraphicsContext.saveGraphicsState();NSGraphicsContext.current=nsctx
func text(_ value:String,_ x:CGFloat,_ y:CGFloat,_ size:CGFloat,_ c:NSColor,_ weight:NSFont.Weight) {
 let attrs:[NSAttributedString.Key:Any]=[.font:NSFont.systemFont(ofSize:size,weight:weight),.foregroundColor:c,.kern:2.0]
 (value as NSString).draw(at:CGPoint(x:x,y:y),withAttributes:attrs)
}
let logoURL = URL(fileURLWithPath: CommandLine.arguments[2]) as CFURL
let logoSource = CGImageSourceCreateWithURL(logoURL, nil)!
let logo = CGImageSourceCreateImageAtIndex(logoSource, 0, nil)!
ctx.draw(logo, in: CGRect(x: 40, y: 42, width: 250, height: 96))
let subtitle = "EUCLIDEAN GRAIN WEAVER"
let subtitleAttributes: [NSAttributedString.Key:Any] = [.font:NSFont.systemFont(ofSize:12, weight:.semibold), .kern:2.0]
let subtitleWidth = (subtitle as NSString).size(withAttributes:subtitleAttributes).width
text(subtitle, 163 - subtitleWidth / 2, 38, 12, NSColor(calibratedRed:0.95,green:0.60,blue:0.22,alpha:0.95), .semibold)
NSGraphicsContext.restoreGraphicsState()
let dest=CGImageDestinationCreateWithURL(URL(fileURLWithPath:CommandLine.arguments[1]) as CFURL,UTType.png.identifier as CFString,1,nil)!
CGImageDestinationAddImage(dest,ctx.makeImage()!,nil);if !CGImageDestinationFinalize(dest){exit(1)}
