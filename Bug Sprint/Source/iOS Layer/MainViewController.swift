//
//  MainViewController.swift
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

import GLKit


class MainViewController: GLKViewController
{
    var core: CoreAdapter!
    var glkView: GLKView!
    var activeTouches = [Int : UITouch]()
    var currentTouchId = 0


    override func viewDidLoad()
    {
        super.viewDidLoad()

        self.glkView = self.view as! GLKView
        self.glkView.context = EAGLContext(api: .openGLES3)
        EAGLContext.setCurrent(self.glkView.context)

        var size = self.view.frame.size
        size.width *= UIScreen.main.scale
        size.height *= UIScreen.main.scale
        self.core = CoreAdapter(viewSize: size)
    }


    func update()
    {
        self.core.update(self.timeSinceLastUpdate)
    }


    func touchIdFor(previousTouch: UITouch) -> Int
    {
        for (touchId, touch) in activeTouches {
            if previousTouch.isEqual(touch) {
                return touchId
            }
        }

        return -1
    }


    override func glkView(_ view: GLKView, drawIn rect: CGRect)
    {
        self.core.draw()
    }


    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        for touch in touches {
            let touchLocation = touch.location(in: self.view)

            let touchId = self.currentTouchId
            self.currentTouchId += 1
            self.activeTouches[touchId] = touch

            self.core.touchDown(withId: touchId, x: Int(touchLocation.x), y: Int(self.view.frame.size.height - touchLocation.y))
        }
    }


    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        for touch in touches {
            let touchLocation = touch.location(in: self.view)

            let touchId = touchIdFor(previousTouch: touch)
            self.activeTouches.removeValue(forKey: touchId)

            self.core.touchUp(withId: touchId, x: Int(touchLocation.x), y: Int(self.view.frame.size.height - touchLocation.y))
        }
    }


    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        for touch in touches {
            let touchLocation = touch.location(in: self.view)

            let touchId = touchIdFor(previousTouch: touch)
            self.activeTouches[touchId] = touch

            self.core.touchMove(withId: touchId, x: Int(touchLocation.x), y: Int(self.view.frame.size.height - touchLocation.y))
        }
    }


    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        for touch in touches {
            let touchId = touchIdFor(previousTouch: touch)
            self.activeTouches.removeValue(forKey: touchId)

            self.core.touchCancel(withId: touchId)
        }
    }
}
