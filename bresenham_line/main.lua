-- Constantes
COLOR = 1
CLICK_COUNT = 0
LINE_BUFFER = {}

local function createMap(rows, cols)
	--[[
  --  Cria uma Grid com tables
  --
  --  params:
  --    rows (number): número de linhas
  --    cols (number): número de colunas
  --  returns:
  --    table: Grid zerada
  --]]
	local map = {}
	for i = 1, rows do
		map[i] = {}
		for j = 1, cols do
			map[i][j] = 0
		end
	end
	return map
end

local function bresenham(map, x1, y1, x2, y2)
	--[[
  -- Desenha linhas através de Bresenham
  --
  -- params:
  --  map (table): Grid para desenho
  --  x1 (number): coordenada x do ponto incial
  --  y1 (number): coordenada y do ponto incial
  --  x2 (number): coordenada x do ponto final
  --  y2 (number): coordenada y do ponto final
  --]]

	local dx, dy = x2 - x1, y2 - y1
	local yi, xi = 1, 1

	if dy < 0 then
		yi = -1
		dy = -dy
	end

	if dx < 0 then
		xi = -1
		dx = -dx
	end

	local d = 2 * dy - dx
	local incE, incNE = 2 * dy, 2 * (dy - dx)
	local x, y = x1, y1

	map[y][x] = COLOR
	while x ~= x2 do
		if d <= 0 then
			d = d + incE
			x = x + xi
		else
			d = d + incNE
			x = x + xi
			y = y + yi
		end
		map[y][x] = COLOR
	end

	while y ~= y2 do
		y = y + yi
		map[y][x] = COLOR
	end
end

function love.load()
	love.window.setTitle("Bresenham Algorithm")
	love.window.setMode(800, 600)
	Map = createMap(20, 20)
end

function love.update(dt)
	if love.keyboard.isDown("c") then
		Map = createMap(20, 20)
	end
end

function love.mousepressed(x, y, button, istouch)
	if button == 1 then
		local grid_x = math.floor((x - 125) / 25)
		local grid_y = #Map - math.floor((y - 25) / 25)
		table.insert(LINE_BUFFER, grid_x)
		table.insert(LINE_BUFFER, grid_y)
		print(string.format("x_grid = %d, y_grid = %d", grid_x, grid_y))
		CLICK_COUNT = CLICK_COUNT + 1

		if CLICK_COUNT == 2 then
			bresenham(Map, LINE_BUFFER[1], LINE_BUFFER[2], LINE_BUFFER[3], LINE_BUFFER[4])
			CLICK_COUNT = 0
			LINE_BUFFER = {}
		end
	end
end

function love.draw()
	for y = #Map, 1, -1 do
		for x = 1, #Map[y] do
			local screenY = (#Map - y) * 25
			if Map[y][x] == 0 then
				love.graphics.setColor(0.6, 0.6, 0.6)
				love.graphics.rectangle("line", x * 25 + 125, screenY + 25, 25, 25)
			elseif Map[y][x] == 1 then
				love.graphics.setColor(1, 1, 1)
				love.graphics.rectangle("fill", x * 25 + 125, screenY + 25, 25, 25)
			end
		end
	end

	love.graphics.setColor(0.2, 0.8, 0.2, 1)
	love.graphics.printf("Click in 2 points to create a line", 0, 540, 800, "center")
	love.graphics.printf("Press C to clear the grid", 0, 560, 800, "center")
end
