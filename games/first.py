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

    def create_surface(self,x,y):
        surface = pygame.Surface(self.display.get_size())
        surface.fill((255,255,255))
        surface = surface.convert()        
        self.surfaces[(x,y)] = surface

    def start(self):
        pygame.init()
        self.display = pygame.display.set_mode((self.width, self.height))

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
        

    def draw_surfaces(self):
        for coords , surface in self.surfaces.iteritems():
            self.display.blit(surface, (coords[0],coords[1]))

    def stop(self):
        pygame.quit()

if __name__ == "__main__":
    engine = GameEngine(640,480,30)
    engine.start()
    engine.create_surface(0,0)
    engine.process()
    engine.stop()



