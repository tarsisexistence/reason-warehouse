let getTimeDescription = (article: Typings.dashboardArticle) => {
  let date = Js.Date.fromString(article.date_created);
  let month =
    date |> Js.Date.getMonth |> int_of_float |> Utils.Common.getMonthName;
  let day = date |> Js.Date.getDate;
  let year = date |> Js.Date.getFullYear;
  let readingTime = (article.timing |> Js.Int.toFloat) /. 60.0 |> Js.Math.ceil;
  {j|$month $day, $year • $readingTime min read|j};
};

[@react.component]
let make = (~article: Typings.dashboardArticle) => {
  let href = "articles/" ++ article.id;

  <article
    style={ReactDOMRe.Style.make(~display="block", ~padding="30px 0", ())}>
    <a
      href
      onClick={event => {
        ReactEvent.Mouse.preventDefault(event);
        ReasonReactRouter.push(href);
      }}
      style={ReactDOMRe.Style.make(
        ~fontSize="1.75rem",
        ~fontWeight="700",
        ~marginBottom="0.4375rem",
        ~boxShadow="none",
        ~display="block",
        (),
      )}>
      {article.title |> React.string}
    </a>
    <small style={ReactDOMRe.Style.make(~fontSize="80%", ())}>
      {article |> getTimeDescription |> React.string}
    </small>
    <p> {"Let clean code guide you. Then let it go" |> React.string} </p>
  </article>;
};