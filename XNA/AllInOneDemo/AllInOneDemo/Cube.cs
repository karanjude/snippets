using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;


namespace MyGame
{
    public class Cube
    {
        private GraphicsDevice graphics;
        VertexPositionColor[] nonIndexedCube = new VertexPositionColor[36];
        VertexDeclaration basicEffectVertexDeclaration;
        VertexBuffer vertexBuffer;
        BasicEffect basicEffect;
        Matrix worldMatrix;
        Matrix viewMatrix;
        Matrix projectionMatrix;

        Vector3 topLeftFront = new Vector3(-1.0f, 1.0f, 1.0f);
        Vector3 bottomLeftFront = new Vector3(-1.0f, -1.0f, 1.0f);
        Vector3 topRightFront = new Vector3(1.0f, 1.0f, 1.0f);
        Vector3 bottomRightFront = new Vector3(1.0f, -1.0f, 1.0f);
        Vector3 topLeftBack = new Vector3(-1.0f, 1.0f, -1.0f);
        Vector3 topRightBack = new Vector3(1.0f, 1.0f, -1.0f);
        Vector3 bottomLeftBack = new Vector3(-1.0f, -1.0f, -1.0f);
        Vector3 bottomRightBack = new Vector3(1.0f, -1.0f, -1.0f);

        Vector2 textureTopLeft = new Vector2(0.0f, 0.0f);
        Vector2 textureTopRight = new Vector2(1.0f, 0.0f);
        Vector2 textureBottomLeft = new Vector2(0.0f, 1.0f);
        Vector2 textureBottomRight = new Vector2(1.0f, 1.0f);

        Vector3 frontNormal = new Vector3(0.0f, 0.0f, 1.0f);
        Vector3 backNormal = new Vector3(0.0f, 0.0f, -1.0f);
        Vector3 topNormal = new Vector3(0.0f, 1.0f, 0.0f);
        Vector3 bottomNormal = new Vector3(0.0f, -1.0f, 0.0f);
        Vector3 leftNormal = new Vector3(-1.0f, 0.0f, 0.0f);
        Vector3 rightNormal = new Vector3(1.0f, 0.0f, 0.0f);


        private void InitializeMatrices()
        {
            float tilt = MathHelper.ToRadians(22.5f);
            worldMatrix = Matrix.CreateRotationX(tilt) * Matrix.CreateRotationY(tilt);
            viewMatrix = Matrix.CreateLookAt(new Vector3(0, 0, 5), Vector3.Zero, Vector3.Up);
            projectionMatrix = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45),
                (float)graphics.Viewport.Width / (float)graphics.Viewport.Height, 1.0f, 100.0f);

        }

        private void InitializeEffect()
        {
            basicEffect = new BasicEffect(graphics, null);
            //basicEffect.Alpha = 1.0f;
            //basicEffect.DiffuseColor = new Vector3(1.0f, 0.0f, 1.0f);
            basicEffect.SpecularColor = new Vector3(0.25f, 0.25f, 0.25f);
            basicEffect.SpecularPower = 5.0f;
            basicEffect.AmbientLightColor = new Vector3(0.75f, 0.75f, 0.75f);

          

          

            basicEffect.World = worldMatrix;
            basicEffect.View = viewMatrix;
            basicEffect.Projection = projectionMatrix;

        }

        private void InitializeVertices()
        {
            nonIndexedCube[0] =
    new VertexPositionColor( topLeftFront,Color.Green);
            nonIndexedCube[1] =
                new VertexPositionColor(
                bottomLeftFront, Color.Green);
            nonIndexedCube[2] =
                new VertexPositionColor(
                topRightFront, Color.Green);
            nonIndexedCube[3] =
                new VertexPositionColor(
                bottomLeftFront, Color.Green);
            nonIndexedCube[4] =
                new VertexPositionColor(
                bottomRightFront, Color.Green);
            nonIndexedCube[5] =
                new VertexPositionColor(
                topRightFront, Color.Green);

            // Back face 
            nonIndexedCube[6] =
                new VertexPositionColor(
                topLeftBack, Color.Green);
            nonIndexedCube[7] =
                new VertexPositionColor(
                topRightBack, Color.Green);
            nonIndexedCube[8] =
                new VertexPositionColor(
                bottomLeftBack, Color.Green);
            nonIndexedCube[9] =
                new VertexPositionColor(
                bottomLeftBack, Color.Green);
            nonIndexedCube[10] =
                new VertexPositionColor(
                topRightBack, Color.Green);
            nonIndexedCube[11] =
                new VertexPositionColor(
                bottomRightBack, Color.Green);

            // Top face
            nonIndexedCube[12] =
                new VertexPositionColor(
                topLeftFront, Color.Green);
            nonIndexedCube[13] =
                new VertexPositionColor(
                topRightBack, Color.Green);
            nonIndexedCube[14] =
                new VertexPositionColor(
                topLeftBack, Color.Green);
            nonIndexedCube[15] =
                new VertexPositionColor(
                topLeftFront, Color.Green);
            nonIndexedCube[16] =
                new VertexPositionColor(
                topRightFront, Color.Green);
            nonIndexedCube[17] =
                new VertexPositionColor(
                topRightBack, Color.Green);

            // Bottom face 
            nonIndexedCube[18] =
                new VertexPositionColor(
                bottomLeftFront, Color.Green);
            nonIndexedCube[19] =
                new VertexPositionColor(
                bottomLeftBack, Color.Green);
            nonIndexedCube[20] =
                new VertexPositionColor(
                bottomRightBack, Color.Green);
            nonIndexedCube[21] =
                new VertexPositionColor(
                bottomLeftFront, Color.Green);
            nonIndexedCube[22] =
                new VertexPositionColor(
                bottomRightBack, Color.Green);
            nonIndexedCube[23] =
                new VertexPositionColor(
                bottomRightFront, Color.Green);

            // Left face
            nonIndexedCube[24] =
                new VertexPositionColor(
                topLeftFront, Color.Green);
            nonIndexedCube[25] =
                new VertexPositionColor(
                bottomLeftBack, Color.Green);
            nonIndexedCube[26] =
                new VertexPositionColor(
                bottomLeftFront, Color.Green);
            nonIndexedCube[27] =
                new VertexPositionColor(
                topLeftBack, Color.Green);
            nonIndexedCube[28] =
                new VertexPositionColor(
                bottomLeftBack, Color.Green);
            nonIndexedCube[29] =
                new VertexPositionColor(
                topLeftFront, Color.Green);

            // Right face 
            nonIndexedCube[30] =
                new VertexPositionColor(
                topRightFront, Color.Green);
            nonIndexedCube[31] =
                new VertexPositionColor(
                bottomRightFront, Color.Green);
            nonIndexedCube[32] =
                new VertexPositionColor(
                bottomRightBack, Color.Green);
            nonIndexedCube[33] =
                new VertexPositionColor(
                topRightBack, Color.Green);
            nonIndexedCube[34] =
                new VertexPositionColor(
                topRightFront, Color.Green);
            nonIndexedCube[35] =
                new VertexPositionColor(
                bottomRightBack, Color.Green);

        }

        private void InitializeVertexBuffer()
        {
            vertexBuffer = new VertexBuffer(graphics, VertexPositionColor.SizeInBytes * nonIndexedCube.Length, ResourceUsage.None, ResourceManagementMode.Automatic);
            vertexBuffer.SetData<VertexPositionColor>(nonIndexedCube);
            basicEffectVertexDeclaration = new VertexDeclaration(graphics, VertexPositionColor.VertexElements);
        }

        public void Initialize(GraphicsDevice graphics)
        {
            this.graphics = graphics;
            // Front face
            InitializeMatrices();
            InitializeEffect();
            InitializeVertices();
            InitializeVertexBuffer();
        }

        public void Draw()
        {
            graphics.VertexDeclaration = basicEffectVertexDeclaration;
            graphics.Vertices[0].SetSource(vertexBuffer, 0, VertexPositionColor.SizeInBytes);
            graphics.RenderState.CullMode = CullMode.CullClockwiseFace;
            basicEffect.Begin();
            foreach (EffectPass pass in basicEffect.CurrentTechnique.Passes)
            {
                pass.Begin();
                graphics.DrawPrimitives(PrimitiveType.TriangleList, 0, 12);
                pass.End();
            }
            basicEffect.End();
         
        }
    }
}
