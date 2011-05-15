# -*- coding: utf-8 -*-

import engine

if __name__ == "__main__":
    engine = engine.GameEngine(640,480,30)
    engine.start()
    engine.create_surface(50,50,"ballsurface", 320, 240)
    engine.draw_circle(0, 0, 255, 25, 25, 25, "ballsurface")
    engine.draw_circle(0,200,0, 200,50, 35,"background")
    engine.draw_rectangle(0, 255, 0, 50, 50, 100, 25, "background")
    engine.process()
    engine.stop()



