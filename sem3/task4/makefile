# Директории для исходных кодов и скомпилированных файлов
SRC_DIR := src
BIN_DIR := bin

# Перечень всех Java файлов
JAVA_FILES := AreaChecker.java ControllerServlet.java ErrorUtil.java CoordinatesValidator.java AreaCheckServlet.java

# Собранные .class файлы будут иметь такие же имена, но располагаться в BIN_DIR
CLASS_FILES := $(JAVA_FILES:%.java=$(BIN_DIR)/%.class)

# Цель по умолчанию. В данном случае сборка всех .class файлов
all: $(BIN_DIR) $(CLASS_FILES)

# Как превратить .java в .class
$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	javac -d $(BIN_DIR) $<

# Создание директории для скомпилированных файлов
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Удаление всех скомпилированных и временных файлов
clean:
	rm -rf $(BIN_DIR)

# .PHONY указывает, что clean и all — не файлы, а команды для make
.PHONY: all clean
