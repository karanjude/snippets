# -*- coding: utf-8 -*-

import engine
import random

class MyScene(engine.Scene):
    def __init__(self, engineInstance):
        engine.Scene.__init__(self, engineInstance)
        self.color1 = random.randint(0,255)
        self.color2 = random.randint(0,255)
        self.t = 0

    def render(self):
        self.engine.draw_line(self.color1, 255-self.color1, self.color2, 32 * self.t , 0, 0 , 480-24*self.t, "display")
        self.engine.draw_line(255-self.color2,self.color2,self.color1, 32*self.t,480, 640,480-24*self.t,"display")
        self.engine.render_surface_at("ballsurface", 400, 380)
        self.t += 1
        if self.t > 20:
            self.t = 0
            self.color1 = random.randint(0,255)
            self.color2 = random.randint(0,255)

if __name__ == "__main__":
    gameEngine = engine.GameEngine(640,480,30)
    gameEngine.start()
    gameEngine.create_surface(50,50,"ballsurface", 20, 240)
    gameEngine.draw_circle(0, 0, 255, 25, 25, 25, "ballsurface")
    scene = MyScene(gameEngine)
    gameEngine.process(scene)
    gameEngine.stop()



