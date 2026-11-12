import Foundation
import Vision
import AppKit
import ImageIO

struct Box: Codable { let text: String; let conf: Float; let x: Double; let y: Double; let w: Double; let h: Double }
struct Result: Codable { let file: String; let width: Int; let height: Int; let boxes: [Box] }

var results: [Result] = []
let args = Array(CommandLine.arguments.dropFirst())
for path in args {
    // ImageIO returns the stored pixels without applying EXIF orientation, matching Pillow
    guard let src = CGImageSourceCreateWithURL(URL(fileURLWithPath: path) as CFURL, nil),
          let cg = CGImageSourceCreateImageAtIndex(src, 0, nil) else {
        results.append(Result(file: path, width: 0, height: 0, boxes: [])); continue
    }
    let W = cg.width, H = cg.height
    let req = VNRecognizeTextRequest()
    req.recognitionLevel = .accurate
    req.usesLanguageCorrection = false
    req.recognitionLanguages = ["en-US"]
    let handler = VNImageRequestHandler(cgImage: cg, options: [:])
    var boxes: [Box] = []
    do {
        try handler.perform([req])
        for obs in req.results ?? [] {
            guard let c = obs.topCandidates(1).first else { continue }
            let b = obs.boundingBox // normalized, origin bottom-left
            boxes.append(Box(text: c.string, conf: c.confidence,
                             x: b.minX * Double(W), y: (1 - b.maxY) * Double(H),
                             w: b.width * Double(W), h: b.height * Double(H)))
        }
    } catch { }
    results.append(Result(file: path, width: W, height: H, boxes: boxes))
}
let enc = JSONEncoder(); enc.outputFormatting = [.prettyPrinted]
let data = try! enc.encode(results)
FileHandle.standardOutput.write(data)
