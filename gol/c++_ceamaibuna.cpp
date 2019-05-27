#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
ofstream myfile;

#define WHITE sf::Color::White
#define BLUE sf::Color::Blue
#define RED sf::Color::Red
#define GRAY sf::Color(153, 153, 153)



int wrapValue(int v, int vMax)
{
    if (v == -1)
        return vMax - 1;
    if (v == vMax)
        return 0;
    return v;
}
string precedentGrid(int grid[])
{
            ifstream myfile;
            ofstream os;
            

            
            int i = 0;
            myfile.open("filetext.txt");
            os.open("b.txt");
            int lineNo = 0;
            string line, stringline;
            while (getline(myfile, line))
            {
                lineNo++;
            }
            myfile.close();
            myfile.open("filetext.txt");

            while (i < lineNo - 1)
            {
                i++;
                getline(myfile, stringline);
                os << stringline;
                if (i < lineNo - 1)
                    os << endl;
            }
            myfile.close();
            os.close();
            remove("filetext.txt");
            rename("b.txt", "filetext.txt");
            return line;
            
            
}
void createFileFunction(int N_CELLS, int grid[])
{

    myfile.open("filetext.txt", ios_base::app);
    myfile << 0 << endl;
    if (myfile.is_open())
    {
        for (int count = 0; count < N_CELLS; count++)
        {
            if (grid[count] == 1)
            {
                myfile << count << " ";
            }
        }
    }
    myfile.close();
}

int *extractIntegerWords(string str)
{
    stringstream ss;
    int i = 0;
    static int array[600] = {};

    ss << str;

    string temp;
    int found;
    while (!ss.eof())
    {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
        {
            //cout<< found<<" ";
            array[i] = (int)found;
            ++i;
        }
        /* To save from space at the end of string */
        temp = "";
    } //cout<<endl;
      //for(int f=0;f<i;f++) {cout<<array[f]<<" ";}

    return array;
}

bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp)
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}
int main()
{
    remove("filetext.txt");
    const int CELL_SIZE =30;                             
    const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE); 
    const int GRID_WIDTH = 30;                            
    const int GRID_HEIGHT = 20;                          
    const int N_CELLS = GRID_WIDTH * GRID_HEIGHT;         
    int grid[N_CELLS] = {};
    int gridNext[N_CELLS] = {};
    long countNrOfChars = -1;
    srand(time(NULL));
    for (int i = 0; i < N_CELLS; i++)
        grid[i] = 0;
    

    const int DELAY_INC = 10; 
    int delay = 100;

    bool isPlaying = false;
    bool reverse = false;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text textFps("", font);
    textFps.setCharacterSize(15);
    textFps.setPosition(10, CELL_SIZE * GRID_HEIGHT + 5);
    textFps.setFillColor(RED);

   
    sf::Texture textureButtonP;
    if (!textureButtonP.loadFromFile("button3.png"))
    {
        return 1;
    }
    sf::Texture textureButtonRight;
    if (!textureButtonRight.loadFromFile("button2.png"))
    {
        return 1;
    }
    sf::Texture textureButtonLeft;
    if (!textureButtonLeft.loadFromFile("button1.png"))
    {
        return 1;
    }
    sf::Texture textureButtonReverse;
    if (!textureButtonReverse.loadFromFile("button4.png"))
    {
        return 1;
    }

    sf::Sprite spriteButtonP;
    spriteButtonP.setScale(0.2, 0.2);
    spriteButtonP.setTexture(textureButtonP);

    sf::Sprite spriteButtonRight;
    spriteButtonRight.setScale(0.15, 0.15);
    spriteButtonRight.setTexture(textureButtonRight);

    sf::Sprite spriteButtonLeft;
    spriteButtonLeft.setScale(0.15, 0.15);
    spriteButtonLeft.setTexture(textureButtonLeft);

    sf::Sprite spriteButtonReverse;
    spriteButtonReverse.setScale(0.15, 0.15);
    spriteButtonReverse.setTexture(textureButtonReverse);

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT + 50), "Game of Life");
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                remove("filetext.txt");
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::P)
                    isPlaying = !isPlaying;
                else if (event.key.code == sf::Keyboard::Right)
                    delay = std::max(delay - DELAY_INC, 0);
                else if (event.key.code == sf::Keyboard::Left)
                    delay += DELAY_INC;
                break;
            case sf::Event::MouseButtonPressed:
                if (!isPlaying && event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = double(event.mouseButton.x) / CELL_SIZE;
                    int y = double(event.mouseButton.y) / CELL_SIZE;
                    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
                        grid[x + y * GRID_WIDTH] = !grid[x + y * GRID_WIDTH];
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (isSpriteHover(spriteButtonP.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        isPlaying = !isPlaying;
                    }
                }
                else if (isSpriteHover(spriteButtonRight.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        delay = std::max(delay - DELAY_INC, 0);
                    }
                }
                else if (isSpriteHover(spriteButtonLeft.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        delay += DELAY_INC;
                    }
                }
                else if (isSpriteHover(spriteButtonReverse.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        reverse = true;
                    }
                }
                break;
            }
        }

        if (isPlaying)
            createFileFunction(N_CELLS, grid);
        if (reverse)
        {   int *p;
        	reverse=false;
        	
        	p = extractIntegerWords(precedentGrid(grid));
            
            for (int f = 0; f < N_CELLS; f++)
                grid[f] = 0;
            for (int f = 0; p[f] != 0; f++)
            	grid[p[f]] = 1;
        }

       
        window.clear(GRAY);
        for (int x = 0; x < GRID_WIDTH; x++)//TODO drawFunction void
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {
                

                sf::RectangleShape cell;
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                cell.setSize(CELL_VECTOR);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(GRAY);
                if (grid[x + y * GRID_WIDTH] != 0)
                    cell.setFillColor(BLUE);
                else
                    cell.setFillColor(WHITE);
                window.draw(cell);

             
                if (isPlaying)
                {
                    int neighborSum = 0;//TODO nextgrid function
                    for (int i = -1; i < 2; i++)
                        for (int j = -1; j < 2; j++)
                        {
                            int xi = wrapValue(x + i, GRID_WIDTH);
                            int yj = wrapValue(y + j, GRID_HEIGHT);
                            neighborSum += grid[xi + yj * GRID_WIDTH];
                        }

                    int current = x + y * GRID_WIDTH;
                    neighborSum -= grid[current];
                    gridNext[current] = grid[current];
                    if (grid[current] == 1 && (neighborSum < 2 || neighborSum > 3))
                        gridNext[current] = 0;
                    else if (neighborSum == 3)
                        gridNext[current] = 1;
                }
            }
        }

       
        sf::Time time = clock.getElapsedTime();
        std::cout << fixed << setprecision(2) << 1.0f / time.asSeconds() << std::endl;

        clock.restart().asSeconds();

        sf::Text textFps("FPS: " + std::to_string(1 / time.asSeconds()), font);//goto up set text size
        textFps.setCharacterSize(25);
        textFps.setPosition(10, CELL_SIZE * GRID_HEIGHT + 5);
        textFps.setFillColor(RED);
       	window.draw(textFps);
        if (isPlaying)
            for (int i = 0; i < N_CELLS; i++)
                grid[i] = gridNext[i];

       

       
        

        spriteButtonRight.setPosition(400, CELL_SIZE * GRID_HEIGHT - 10);
        window.draw(spriteButtonRight);

        spriteButtonP.setPosition(285, CELL_SIZE * GRID_HEIGHT - 29);
        window.draw(spriteButtonP);

        spriteButtonLeft.setPosition(200, CELL_SIZE * GRID_HEIGHT - 10);
        window.draw(spriteButtonLeft);

        spriteButtonReverse.setPosition(750, CELL_SIZE * GRID_HEIGHT + 10);
        window.draw(spriteButtonReverse);

        window.display();

        sf::sleep(sf::milliseconds(delay));
    }
}
