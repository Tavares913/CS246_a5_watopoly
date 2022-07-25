CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = main.o academic_building.o auction.o collect_osap.o coop_fee.o dc_tims_line.o display.o gameboard.o go_to_tims.o goose_nesting.o gym.o needles_hall.o non_property.o observer.o player.o property.o residence.o slc.o subject.o tile.o tuition.o watopoly.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}