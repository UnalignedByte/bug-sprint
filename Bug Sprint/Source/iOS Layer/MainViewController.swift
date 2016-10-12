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

        self.core = CoreAdapter(size: self.view.frame.size)
    }


    func update()
    {
        self.core.update(self.timeSinceLastUpdate)
    }


    override func glkView(_ view: GLKView, drawIn rect: CGRect)
    {
        self.core.draw()
    }
}

