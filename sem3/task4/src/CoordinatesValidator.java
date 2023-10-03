package utils;

import java.util.Arrays;
import java.util.List;

public class CoordinatesValidator {
    private final double x, y, r;

    public CoordinatesValidator(double x, double y, double r) {
        this.x = x;
        this.y = y;
        this.r = r;
    }

    public boolean checkData() {
        if (!checkX()) System.out.println("X validation haven't passed");
        if (!checkY()) System.out.println("Y validation haven't passed");
        if (!checkR()) System.out.println("R validation haven't passed");
        System.out.println(x);
        System.out.println(y);
        System.out.println(r);
        return checkX() && checkY() && checkR();
    }

    private boolean checkX() {
        List<Integer> validXValues = Arrays.asList(-4, -3, -2, -1, 0, 1, 2, 3, 4);
        return validXValues.contains((int) x) && x == (int) x;
    }

    private boolean checkY() {
        return y > -3 && y < 5;
    }

    private boolean checkR() {
        return r > 2 && r <= 5;
    }
}
