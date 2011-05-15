# -*- coding: utf-8 -*-

import pygame

class GameEngine:
    def __init__(self, width, height, fps, debug = True):
        self.clock = pygame.time.Clock()
        self.width = width
        self.height = height
        self.fps = fps
        self.playtime = 0.0
        self.debug = debug
        self.render = True
        self.surfaces = {}
    
    def create_surface(self,width,height,name, x,y):
        surface = pygame.Surface((width, height))
        surface = surface.convert()        
        self.surfaces[name] = (surface,(x,y))

    def init_background(self):
        self.background = pygame.Surface(self.display.get_size())
        self.background.fill((255,255,255))
        self.background = self.background.convert()
        self.surfaces["background"] = (self.background, (0,0))

    def start(self):
        pygame.init()
        self.display = pygame.display.set_mode((self.width, self.height))
        self.init_background()

    def process_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.render = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    self.render = False

    def process(self):
        self.draw_surfaces()
        while self.render:
            milliseconds = self.clock.tick(self.fps) # do not go faster than this framerate
            self.playtime += milliseconds / 1000.0 # add seconds to playtime
            if self.debug:
                print ("%i milliseconds passed since last frame" % milliseconds ) # brackets for python3.x
            self.process_events()
            if self.debug:
                pygame.display.set_caption("frame rate: %.2f frames per second, playtime: %.2f seonds" % 
                                           (self.clock.get_fps(), self.playtime))
            pygame.display.flip()          # flip the screen like in a flip book
        

    def draw_circle(self, r, g, b, width, height, radius, surface_name):
        surface = self.surfaces[surface_name][0]
        pygame.draw.circle(surface, (r,g,b), (width, height), radius)

    def draw_rectangle(self, r, g, b, x1, y1, width, height, surface_name):
        surface = self.surfaces[surface_name][0]
        pygame.draw.rect(surface, (r,g,b), (x1,y1, width, height))
        
    def draw_surfaces(self):
        self.display.blit(self.background, (0,0))
        print self.surfaces
        for k,v in self.surfaces.iteritems():
            if k == "background":
                continue
            surface = v[0]
            coords = v[1]
            self.display.blit(surface, (coords[0],coords[1]))

    def stop(self):
        self.surfaces.clear()
        pygame.quit()

if __name__ == "__main__":
    engine = GameEngine(640,480,30)
    engine.start()
    engine.create_surface(50,50,"ballsurface", 320, 240)
    engine.draw_circle(0, 0, 255, 25, 25, 25, "ballsurface")
    engine.draw_circle(0,200,0, 200,50, 35,"background")
    engine.draw_rectangle(0, 255, 0, 50, 50, 100, 25, "background")
    engine.process()
    engine.stop()



