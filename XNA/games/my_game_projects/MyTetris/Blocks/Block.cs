using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MyTetris.Movements;

namespace MyTetris
{
    public abstract class Block
    {
        protected Texture2D backgroundTexture;
        protected Vector2 position;
        
        protected Square square1;
        protected Square square2;
        protected Square square3;
        protected Square square4;

        protected Vector2 _oldSquare1Position;
        protected Vector2 _oldSquare2Position;
        protected Vector2 _oldSquare3Position;
        protected Vector2 _oldSquare4Position;

        protected GameField gameField;

        private Direction direction;
        private Movements.Movements movements;


        public Block(GameField gameField, Texture2D backgroundTexture, Vector2 origin , Direction direction)
        {
            this.backgroundTexture = backgroundTexture;
            this.position = origin;
            this.direction = direction;
            this.gameField = gameField;

            square1 = new Square(this.backgroundTexture, position);
            square2 = new Square(this.backgroundTexture, position);
            square3 = new Square(this.backgroundTexture, position);
            square4 = new Square(this.backgroundTexture, position);

            movements = new Movements.Movements(this,gameField);

            setupBlock();
        }

        public abstract void RotateTo(North north);

        public abstract void RotateTo(East east);

        public abstract void RotateTo(West west);

        public abstract void RotateTo(South south);

        public void Rotate()
        {
            savePositions();
            this.direction = direction.Rotate(this);
            if (!canRotate())
                revertPositions();
        }

        public virtual void MoveLeft(int units)
        {
            savePositions();
            if (movements.LEFT.CanMove(units))
            {
                square1.MoveLeft(units);
                square2.MoveLeft(units);
                square3.MoveLeft(units);
                square4.MoveLeft(units);
            }
            else
                revertPositions();
        }

        public virtual void MoveRight(int units)
        {
            savePositions();
            if (movements.RIGHT.CanMove(units))
            {
                square1.MoveRight(units);
                square2.MoveRight(units);
                square3.MoveRight(units);
                square4.MoveRight(units);
            }
            else
                revertPositions();
        }

        public virtual bool MoveDown(int units)
        {
            bool result = false;
            savePositions();
            if (movements.DOWN.CanMove(units))
            {
                result = true;
                square1.MoveDown(units);
                square2.MoveDown(units);
                square3.MoveDown(units);
                square4.MoveDown(units);
            }
            else
                revertPositions();
            return result;
        }

        public virtual void Draw(SpriteBatch batch)
        {
            batch.Draw(square1.Texture, square1.Position, Color.White);
            batch.Draw(square2.Texture, square2.Position, Color.White);
            batch.Draw(square3.Texture, square3.Position, Color.White);
            batch.Draw(square4.Texture, square4.Position, Color.White);
        }


        public void UpdateStateInGameField()
        {
            gameField.UpdateGameFieldStateForSquare(square1.Position);
            gameField.UpdateGameFieldStateForSquare(square2.Position);
            gameField.UpdateGameFieldStateForSquare(square3.Position);
            gameField.UpdateGameFieldStateForSquare(square4.Position);
      
        }

        public Square Square1
        {
            get { return this.square1; }
        }

        public Square Square2
        {
            get { return this.square2; }
        }

        public Square Square3
        {
            get { return this.square3; }
        }

        public Square Square4
        {
            get { return this.square4; }
        }


        protected virtual void setupBlock()
        {
            Rotate();
        }

        protected void savePositions()
        {
            _oldSquare1Position = square1.Position;
            _oldSquare2Position = square2.Position;
            _oldSquare3Position = square3.Position;
            _oldSquare4Position = square4.Position;
        }

        protected bool canRotate()
        {
            return canRotate(square1) &&
                canRotate(square2) &&
                canRotate(square3) &&
                canRotate(square4);
        }

        protected void revertPositions()
        {
            square1.Position = _oldSquare1Position;
            square2.Position = _oldSquare2Position;
            square3.Position = _oldSquare3Position;
            square4.Position = _oldSquare4Position;
       }

        private bool canRotate(Square square)
        {
            return gameField.CanRotate(square);
        }


    }
}
