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


    override func glkView(_ view: GLKView, drawIn rect: CGRect)
    {
        self.core.draw()
    }


    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        if let touch = touches.first {
            let touchLocation = touch.location(in: self.view)

            self.core.touchDownAt(x: Int(touchLocation.x), y: Int(self.view.frame.size.height - touchLocation.y))
        }
    }


    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        if let touch = touches.first {
            let touchLocation = touch.location(in: self.view)

            self.core.touchUpAt(x: Int(touchLocation.x), y: Int(self.view.frame.size.height - touchLocation.y))
        }
    }


    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        if let touch = touches.first {
            let touchLocation = touch.location(in: self.view)

            self.core.touchMoveAt(x: Int(touchLocation.x), y: Int(self.view.frame.size.height - touchLocation.y))
        }
    }


    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        self.core.touchCancel()
    }
}
