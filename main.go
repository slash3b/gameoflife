package main

import (
	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type Game struct{}

func (g *Game) Update() error {
	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	ebitenutil.DebugPrint(screen, "Hello Ilya")
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	return outsideWidth, outsideHeight
}

func main() {
	// ebiten.SetWindowSize(640, 480)
	ebiten.MaximizeWindow()
	ebiten.SetWindowTitle("hello")

	g := &Game{}
	if err := ebiten.RunGame(g); err != nil {
		panic(err)
	}
}
