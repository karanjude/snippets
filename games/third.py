# -*- coding: utf-8 -*-

import engine
import random
import os

class MyScene(engine.Scene):
    def __init__(self, engineInstance):
        engine.Scene.__init__(self, engineInstance)

    def render(self):
        self.engine.render_image_at("colormonster", 0, 300)
        self.engine.render_image_at("colormonster1", 50, 50)

if __name__ == "__main__":
    gameEngine = engine.GameEngine(640,480,30)
    gameEngine.start()
    gameEngine.create_surface(50,50,"ballsurface", 20, 240)
    gameEngine.load_image("background_image",os.path.join(os.getcwd(),"data","800px-La_naissance_de_Venus.jpg"))
    gameEngine.render_image("background_image","background", 640, 480)
    gameEngine.load_image("colormonster",os.path.join(os.getcwd(),"data","colormonster.png"), transparent_color = (255,255,255))
    gameEngine.clone_image("colormonster1","colormonster")
    gameEngine.process(MyScene(gameEngine))
    gameEngine.stop()



