package servlets;

import beans.ResultsBean;
import utils.AreaChecker;
import utils.CoordinatesValidator;
import utils.ErrorUtil;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/check")
public class AreaCheckServlet extends HttpServlet {
    public static final int SC_UNPROCESSABLE_ENTITY = 422;
    public static final int SC_INTERNAL_SERVER_ERROR = 500;
    public static final int SC_BAD_REQUEST = 400;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            double x = ControllerServlet.getDouble(request, "x");
            double y = ControllerServlet.getDouble(request, "y");
            double r = ControllerServlet.getDouble(request, "r");

            CoordinatesValidator validator = new CoordinatesValidator(x, y, r);

            if (!validator.checkData()) {
                System.out.println("validation haven't passed");
                ErrorUtil.sendError(response, SC_UNPROCESSABLE_ENTITY, "Data haven't passed validation");
                return;
            }

            boolean isHit = AreaChecker.isInArea(x, y, r);

            ResultsBean bean = (ResultsBean) request.getSession().getAttribute("results");
            if (bean == null) {
                bean = new ResultsBean();
                request.getSession().setAttribute("results", bean);
            }

            ResultsBean.Result result = new ResultsBean.Result(String.valueOf(x), String.valueOf(y), String.valueOf(r), isHit);
            bean.addResult(result);

            response.sendRedirect("table.jsp");
        } catch (NumberFormatException e) {
            ErrorUtil.sendError(response, SC_BAD_REQUEST, "Invalid number format");
        } catch (Exception e) {
            e.printStackTrace();
            ErrorUtil.sendError(response, SC_INTERNAL_SERVER_ERROR, "Internal Server Error");
        }
    }
}
